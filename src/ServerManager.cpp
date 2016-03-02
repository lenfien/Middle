//
// Created by lenfien on 15/11/4.
//


#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <fcntl.h>
#include "ServerManager.h"
#include "Debug.h"

ServerManager ServerManager::serverManagerTemplate(server_path);

using namespace std;
ServerManager::ServerManager(std::string path) {
    char cwdBack[255];
    getcwd(cwdBack, sizeof(cwdBack));
    DIR *dir = opendir(path.c_str());
    if(dir == NULL) {
        system_err << path.c_str() << std::endl;
        throw ServerManagerException("Configuration path can not opened.");
    }

    struct dirent *ent = readdir(dir);
    for (; ent != NULL; ent = readdir(dir)) {
        std::string name(ent->d_name);
        if (name == "." || name == ".." || name[0] == '.') {
            continue;
        }

        chdir(path.c_str());
        ifstream ifs(ent->d_name);
        if(!ifs) {
            system_err << "Open " << ent->d_name << "fail:" << strerror(errno) <<std::endl;
            exit(1);
        }

        int count = 0;
        Server *server = new Server();
        server->set_name(name);

        while (ifs.good()) {
            string line;
            std::getline(ifs, line, '\n');
            if(line.empty() || line[0] == '#')
                continue;

            std::istringstream iss(line);

            if (count == 0) {
                string ip;
                in_port_t port;
                iss >> ip >> port;
                server->set_ip(ip);
                server->set_port(port);
            }
            else {
                int16_t id;
                int16_t prio;
                iss >> std::hex >> id >> std::dec >> prio;
                //server->idPrio[id] = prio;
            }

            count ++;
        }

        serverList.push_back(server);
        index_name[name] = (*serverList.rbegin());
        index_fd[server->get_sock()] = (*serverList.rbegin());
        fdCount ++;
    }

    connPools = new pollfd[fdCount];
    closedir(dir);
    chdir(cwdBack);
}

ServerManager::ServerManager(const ServerManager& sm) {
    for (auto pserv : sm.serverList) {
        Server *serv = new Server(*pserv);
        serverList.push_back (serv);
        index_fd[serv->get_sock()] = serv;
        index_name[serv->get_name()] = serv;
        fdCount ++;
    }

    connPools = new pollfd[fdCount];

    /* 启动连接线程 */
    int er;
    er = pthread_create(&connThread, nullptr, connect_thread, this);
    if (er == -1) {
        system_err << "pthread_create fail:" << strerror(errno) << std::endl;
        throw ServerManagerException("pthread create fail!");
    }
}

ServerManager::~ServerManager() {
    pthread_join(connThread, nullptr);
    if(connPools)
        delete [] connPools;

    pthread_rwlock_destroy(&rwl_index_fd);
    pthread_rwlock_destroy(&rwl_index_name);

    for (auto it : serverList)
        delete it;

    //log << "ServerManager 使用的资源已被释放" << std::endl;
}

void *ServerManager::connect_thread(void *param) {
    ServerManager* pserver = (ServerManager*)param;
    ServerManager &self = *(pserver);
    bool allDone = false;
    int connCounter = 0;
    for (auto& it : self.serverList) {
        it->set_status(Server::CONNECTTING);
        if (it->connect_to(false))
            it->set_status(Server::CONNECTED);
    }

    bool loop = true;
    while (loop) {
        connCounter = 0;
        for (auto& it : self.serverList) {
            if (it->get_status() == Server::CONNECTTING) {
                self.connPools[connCounter].fd = it->get_sock();
                self.connPools[connCounter].events = POLLIN | POLLRDNORM | POLLOUT;
                connCounter++;
            }
        }

        if (!allDone) {
            allDone = true;
            for (auto &it : self.serverList) {
                if (it->get_status() == Server::CONNECTTING) {
                    allDone = false;
                    break;
                }
            }
        }

        if (allDone)
            loop = false;

        int pollRes = 0;
        do {
            pollRes = poll(self.connPools, (nfds_t) connCounter, 3000);
            if (pollRes == -1) {
                if (errno == EINTR)
                    continue;

                system_err << "poll return -1:" << strerror(errno) << std::endl;
            }
        } while ( false );

        if (pollRes == 0 || pollRes < 0) {
            for (auto& it : self.serverList) {
                if (it->get_status() == Server::CONNECTTING) {
                    it->set_status(Server::FAIL);
                    sys_log << "服务器:" << it->get_name() << "连接失败 :" << "超时" << std::endl;
                }
            }
            continue;
        }

        for (int i = 0; i < connCounter; i ++) {
            int sock = self.connPools[i].fd;
            short res = self.connPools[i].revents;

            if((res & POLLIN) || (res & POLLOUT) || (res & POLLRDNORM)) {
                int val;
                socklen_t len = sizeof(val);
                getsockopt(sock, SOL_SOCKET, SO_ERROR, &val, &len);
                if(val == 0) {
                    self[sock].set_status(Server::CONNECTED);
                    //log << "服务器:" << self[sock].get_name() << "连接成功" << std::endl;
                }
                else {
                    self[sock].set_status(Server::FAIL);
                    sys_log << "服务器:" << self[sock].get_name() << "连接失败 :" << strerror(val) << std::endl;
                }
            }
        }
    }

    return 0;
}

Server &ServerManager::operator[](int index) {
    Server *pServer = nullptr;
    pthread_rwlock_rdlock(&rwl_index_fd);
    if (index_fd.find(index) == index_fd.end()) {
        pthread_rwlock_unlock(&rwl_index_fd);
        throw std::logic_error(std::string("ServerManager没有找到套接字:") + std::to_string(index));
    }

    pServer = index_fd[index];
    pthread_rwlock_unlock(&rwl_index_fd);
    return *pServer;
}

Server &ServerManager::operator[](std::string name) {
    Server *pServer = nullptr;
    pthread_rwlock_rdlock(&rwl_index_name);
    if (index_name.find(name) == index_name.end()) {
        pthread_rwlock_unlock(&rwl_index_name);
        throw std::logic_error(std::string("ServerManager没有找到名字:") + name);
    }

    pServer = index_name[name];
    pthread_rwlock_unlock(&rwl_index_name);
    return *pServer;
}