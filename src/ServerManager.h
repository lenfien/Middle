//
// Created by lenfien on 15/11/4.
//

#ifndef MIDDLE_SERVERMANAGER_H
#define MIDDLE_SERVERMANAGER_H

#include <set>
#include <list>
#include <string>
#include <poll.h>
#include <pthread.h>
#include <exception>
#include <stdexcept>
#include "Server.h"

class Middle;
class ServerManager {
    friend class Middle;

public:
    static ServerManager serverManagerTemplate;

private:
    std::list<Server*> serverList;
    std::map<std::string, Server*> index_name;          //使用名字索引
    std::map<int, Server*> index_fd;                    //使用套接字索引

    pthread_rwlock_t rwl_index_name = PTHREAD_RWLOCK_INITIALIZER;
    pthread_rwlock_t rwl_index_fd = PTHREAD_RWLOCK_INITIALIZER;

    size_t fdCount = 0;
    pthread_t connThread;
    struct pollfd *connPools;

public:
    ServerManager(std::string path);
    ServerManager(const ServerManager& sm);
    ~ServerManager();

public:
    Server & operator[](int index);

    Server & operator[](std::string name);

private:
    static void *connect_thread(void *param);

};


#endif //MIDDLE_SERVERMANAGER_H
