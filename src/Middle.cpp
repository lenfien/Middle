//
// Created by lenfien on 15/11/5.
//

#include <memory>
#include <unistd.h>
#include <ctime>
#include "Debug.h"
#include "ServerManager.h"
#include "Middle.h"

using namespace std;
size_t Middle::MiddleCounter = 0;
size_t Middle::MiddleRunningCounter = 0;
pthread_rwlock_t Middle::rwl_middleCounter = PTHREAD_RWLOCK_INITIALIZER;
AuthorityManager Middle::authorityManager("/etc/middle_authority");

size_t Middle::get_middle_instance_counter() {
    size_t res = 0;
    pthread_rwlock_rdlock(&rwl_middleCounter);
    res = MiddleRunningCounter;
    pthread_rwlock_unlock(&rwl_middleCounter);
    return res;
}

Middle::Middle(int sock)
        : terminal(sock), serverManager(ServerManager::serverManagerTemplate) {
    pthread_rwlock_wrlock(&rwl_middleCounter);
    middleId = MiddleCounter++;
    MiddleRunningCounter++;
    pthread_rwlock_unlock(&rwl_middleCounter);

    //为将来可能用到的pollfd分配控件,包括所有服务器的和一个Terminal的
    rwPolls = new pollfd[serverManager.serverList.size() + 1];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&middleThread, &attr, middle_thread, this);
    pthread_attr_destroy(&attr);
}

Middle::~Middle() {
    if (rwPolls)
        delete[] rwPolls;

    sys_log << "会话ID[" << middleId << "]:" << "会话结束" << std::endl;

    pthread_rwlock_wrlock(&rwl_middleCounter);
    MiddleRunningCounter--;
    pthread_rwlock_unlock(&rwl_middleCounter);
}

void *Middle::middle_thread(void *param) {
    auto_ptr<Middle> pm(static_cast<Middle *>(param));
    Middle &self = *pm;
    ServerManager &serverManager = self.serverManager;
    Server &mainServer = serverManager["main"];
    Terminal &terminal = self.terminal;
    AuthorityManager &authManager = self.authorityManager;
    time_t lastCommunition = std::time(nullptr);

    bool loop = true;
    int err = 0;
    int counter = 0;

    sys_log << "会话ID[" << self.middleId << "]:" <<
    "为终端[" << terminal.get_name() << "]:" << "begin." << endl;

    std::set<int> connSet;
    while (loop) {
        counter = 0;
        /* 将所有已连接套接字和Terminal的套接字加入到rset中 */
        {
            for (auto serv : serverManager.serverList) {
                if (serv->get_status() == Server::CONNECTED) {
                    self.rwPolls[counter].fd = serv->get_sock();
                    self.rwPolls[counter].revents = 0;
                    self.rwPolls[counter].events = POLLRDNORM;
                    if (serv->get_queue_size() > 0)
                        self.rwPolls[counter].events |= POLLWRNORM;
                    ++counter;
                }
            }

            if (terminal.get_status() == Terminal::CONNECTED) {
                self.rwPolls[counter].fd = terminal.get_sock();
                self.rwPolls[counter].revents = 0;
                self.rwPolls[counter].events = POLLRDNORM;
                if (terminal.get_queue_size() > 0)
                    self.rwPolls[counter].events |= POLLWRNORM;
                ++counter;
            }
        }

        /* 当有一端关闭后 */
        if (mainServer.get_status() == Server::FAIL || terminal.get_status() == Terminal::FAIL) {
            bool canBeSent = false;
            do {
                if (mainServer.get_status() == Server::FAIL && mainServer.get_queue_size() > 0) {
                    canBeSent = true;
                    break;
                }

                for (auto sock : connSet) {
                    if (serverManager[sock].get_queue_size() > 0) {
                        canBeSent = true;
                        break;
                    }
                }
            } while (false);

            if (!canBeSent) {
                loop = false;
                //log << "会话ID[" << self.middleId << "]:" << "主服务器或终端已经断开, 剩余的连接缓存中无要发数据, 准备结束本次回话" << std::endl;
                continue;
            }
            else {
                //log << "会话ID[" << self.middleId << "]:" << "主服务器已经连接但其队列为" <<  serverManager["main"].queue_size() << endl;
            }
        }

        err = poll(self.rwPolls, (nfds_t) counter, 3000);
        if (err == -1) {
            if (errno == EINTR) {
                continue;
            }

            system_err << "poll return -1 :" << strerror(errno) << std::endl;
            loop = false;
            continue;
        }

        if (err == 0) {
            if (std::time(nullptr) - lastCommunition > 300) {
                sys_log << "会话ID[" << self.middleId << "]:--会话已经超时" << endl;
                loop = false;
            }

            continue;
        }

        lastCommunition = std::time(nullptr);
        for (int index = 0; index < counter; index++) {
            int sock = self.rwPolls[index].fd;
            short status = self.rwPolls[index].revents;

#ifdef POLLRDHUP
            if((status & POLLRDNORM) || (status & POLLNVAL) || (status & POLLERR) || (status & POLLHUP)  || (status & POLLRDHUP) )
#else
            if ((status & POLLRDNORM) || (status & POLLNVAL) || (status & POLLERR) || (status & POLLHUP))
#endif
            {
                ssize_t n = read(sock, self.rcvBuffer.data(), self.rcvBuffer.size());
                if (n <= 0) {
                    if (sock == terminal.get_sock()) { /* 如果terminal断开连接了, 则本次服务结束 */
                        terminal.set_status(Terminal::FAIL);
                        terminal.clear_send_queue();
                        sys_log << "会话ID[" << self.middleId << "]:--" << terminal.get_full_name() << "主动断开连接" << std::endl;
                    }
                    else { /*如果是服务器断开连接,则将该服务器的套接字加入到回收站中, 但如果是主服务器断开连接,本次服务同样结束*/
                        try {
                            Server &serv = serverManager[sock];
                            serv.set_status(Server::FAIL);
                            serv.clear_send_queue();

                            sys_log << "会话ID[" << self.middleId << "]:" << serv.get_full_name()
                                << "主动断开连接," << "距离上次发送时间:" << std::time(nullptr) - serv.get_last_send_time()
                                    << "s" << std::endl;

                            continue;
                        }
                        catch (std::logic_error &lex) {
                            system_err << "会话ID[" << self.middleId << "]:" << lex.what() << endl;
                        }
                    }
                }
                else {
                    /*
                     * 如果是从terminal中读来的数据, 则将这些数据加入到所有已连接服务器的写队列中,
                     * 如果主服务器还未连接成功, 也加入到它的写队列中
                     */
                    if (sock == terminal.get_sock()) {
                        list<std::shared_ptr<Message>> result = terminal.get_monitor().run(self.rcvBuffer.data(), n);
                        for (auto &msg : result) {
                            sys_log << "会话ID[" << self.middleId << "]:" << "<<" << terminal.get_full_name() <<
                                msg->to_string(false) << endl;

                            switch(msg->get_msg_id()) {
                                case 0x0102: {
                                    AuthorityMessage* authMsg = dynamic_cast<AuthorityMessage*>(msg.get());
                                    string phoneStr = authMsg->get_phone_str();
                                    string oldAuthoCode = authMsg->get_authority_code();

                                    for (auto &server : serverManager.serverList) {
                                        auto st = server->get_status();
                                        if (st == Server::CONNECTED || st == Server::CONNECTTING) {
                                            if (authManager[server->get_name()].exists(phoneStr)) {
                                                shared_ptr<AuthorityMessage> newAuthMsg(new AuthorityMessage(*authMsg));
                                                newAuthMsg->set_authority_code(authManager[server->get_name()][phoneStr]);
                                                sys_log << "会话ID[" << self.middleId << "]:--"
                                                        << "给服务器" << server->get_full_name() <<"的鉴权消息将"
                                                        << oldAuthoCode << "替换为" << newAuthMsg->get_authority_code() << endl;

                                                shared_ptr<Message> dmsg = newAuthMsg;
                                                server->push(dmsg);
                                            }
                                            else {
                                                sys_log << "会话ID[" << self.middleId << "]--"
                                                        << "在" << server->get_full_name() << "中没有找到" << oldAuthoCode
                                                        << "对应的鉴权码" << endl;

                                                server->push(msg);
                                            }
                                        }
                                    }
                                    break;
                                }

                                case 0x0100: {
                                    sys_log << "会话ID[" << self.middleId << "]:" << "接收到终端注册消息, 加入到所有服务器的写消息队列中" << endl;
                                }
                                //! 注意, 这里不需要有break, 因为接收到的终端注册消息需要加入到所有的服务器写队列中
                                default:
                                    for (auto &server : serverManager.serverList) {
                                        auto st = server->get_status();
                                        if (st == Server::CONNECTED || st == Server::CONNECTTING)
                                            server->push(msg);
                                    }
                                    break;
                            }
                        }
                    }
                    else {
                        /*
                         * 如果数据是从服务器传来的, 依旧读, 这样防止Tcp的读缓存满, 导致Tcp拒绝服务
                         * 如果服务器是main,则将获得到消息包加入到terminal的写队列中.
                         */
                        Server &serv = serverManager[sock];
                        list<std::shared_ptr<Message>> result = serverManager[sock].get_monitor().run(self.rcvBuffer.data(), n);
                        if (result.size() > 0) {
                            for (auto &msg : result) {
                                sys_log << "会话ID[" << self.middleId << "]:" << "<<" <<
                                    serverManager[sock].get_full_name() << ":" << msg->to_string(false) << endl;
                                switch (msg->get_msg_id()) {
                                    case 0x8100: {
                                        MessageRegisterAck * registerAck = dynamic_cast<MessageRegisterAck *>(msg.get());
                                        if (registerAck->is_success()) {
                                            auto& atomKV = authManager[serv.get_name()];
                                            atomKV.add(registerAck->get_phone_str(), registerAck->get_authority_code());
                                            authManager.save_authority(serv.get_name());

                                            sys_log << "会话ID[" << self.middleId << "]:--" << terminal.get_full_name()
                                                 << "在服务器" << serv.get_full_name() << "上注册成功"
                                                    << ", 鉴权码为" << registerAck->get_authority_code() << endl;
                                        }
                                        else {
                                            sys_log << "会话ID[" << self.middleId << "]:--" << terminal.get_full_name()
                                                << "在服务器" << serv.get_full_name() << "上注册失败, " <<
                                                    "原因" << registerAck->get_reason() << endl;
                                        }

                                        if (serv.is_main() && terminal.is_connected()) {
                                            if (registerAck->is_success()) {
                                                registerAck->set_authority_code(registerAck->get_phone_str());
                                                terminal.push(msg);
                                            }
                                            else
                                                terminal.push(msg);
                                        }
                                        break;
                                    }
                                    default:
                                        if (terminal.is_connected() && serv.is_main())
                                            terminal.push(msg);
                                        break;
                                }
                            }
                        }
                    }
                }
            }

            if (status & POLLWRNORM) {
                if (sock == terminal.get_sock()) {
                    try {
                        if (!terminal.send_msg()) {
                            terminal.set_status(Terminal::FAIL);
                            terminal.clear_send_queue();
                            system_err << "会话ID[" << self.middleId << "]:" << "向终端发送数据出错" << endl;
                        }
                        else {
                            sys_log << "会话ID[" << self.middleId << "]:" << ">>" << terminal.get_full_name() << endl;
                        }
                    }
                    catch (std::logic_error &lex) {
                        system_err << "会话ID[" << self.middleId << "]:" << lex.what() << endl;
                        loop = false;
                    }
                }
                else {
                    try
                    {
                        Server &serv = serverManager[sock];
                        if (!serv.send_msg()) {
                            serv.set_status(Server::FAIL);
                            serv.clear_send_queue();

                            system_err << "会话ID[" << self.middleId << "]:" << "向终端发送数据出错" << endl;
                            sys_log << "会话ID[" << self.middleId << "]:" << ">>" << serv.get_full_name() << "服务器"
                                << serv.get_full_name() << "主动断开连接," << "距离上次发送时间:"
                                    << std::time(nullptr) - serv.get_last_send_time() << "s" << std::endl;
                        }
                        else {
                            sys_log << "会话ID[" << self.middleId << "]:" << ">>" << serv.get_full_name() << endl;
                        }
                    }
                    catch (std::logic_error &lex) {
                        system_err << "会话ID[" << self.middleId << "]:" << lex.what() << endl;
                        loop = false;
                    }
                }
            }
        }
    }

    sys_log << "会话ID[" << self.middleId << "]:" << "closed." << endl;
    return NULL;
}