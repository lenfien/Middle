//
// Created by lenfien on 15/11/4.
//

#ifndef MIDDLE_SERVER_H
#define MIDDLE_SERVER_H

#include <map>
#include <memory>
#include <deque>
#include <queue>
#include <fcntl.h>
#include <cstring>
#include <string>
#include <memory>
#include <stdexcept>
#include <vector>
#include "MessageMonitor.h"
#include "Message.h"

#include "Debug.h"
#include "Net.h"

#include "Exceptions.h"
#include "TransmitUnit.h"

class Server : public TransmitUnit {

public:
    friend class ServerManager;

private:
    int oldFlag;    //没有NON_BLOCK的文件描述标识, 用来在非阻塞连接完成后恢复

private:
    std::shared_ptr<MessageRegisterAck> lastRegisterAck = nullptr;

public:
    Server() throw(FDException);
    Server(const Server &serv) throw (std::logic_error, FDException);

public:
    /*
     * 连接到该服务器
     *
     * block 为true时以阻塞形式连接
     * block 为false时,timeout_ms为非阻塞超时时间
     *
     * 成功返回true
     *
     * 即便是block为false,也应检查返回值
     */
    bool connect_to(bool block = true);
    std::shared_ptr<MessageRegisterAck> get_last_register_ack() {return lastRegisterAck;}

    /* 套接字已非阻塞形式连接成功后, 需要将其恢复成阻塞形式的 */
    void restore_sock_flags() { fcntl(sock, F_SETFL, oldFlag); }

public:
    bool is_main() { return name == "main" || name == "Main"; }
};


#endif //MIDDLE_SERVER_H
