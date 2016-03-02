//
// Created by lenfien on 15/11/5.
//

#ifndef MIDDLE_MIDDLE_H
#define MIDDLE_MIDDLE_H

#include <pthread.h>
#include <array>
#include "Terminal.h"
#include "ServerManager.h"
#include "MessageMonitor.h"
#include "AuthorityManager.h"
#include "Server.h"

class Middle {
private:
    static size_t MiddleCounter;   //Middle的使用计数
    static size_t MiddleRunningCounter;
    static pthread_rwlock_t rwl_middleCounter;
    static AuthorityManager authorityManager;

public:
    /* 获取正在运行的Middle的个数 */
    static size_t get_middle_instance_counter();

public:
    Middle(int sock);
    ~Middle();

private:
    size_t middleId;
    Terminal terminal;
    ServerManager serverManager;
    pthread_t middleThread;
    std::array<uint8_t, 256> rcvBuffer;
    struct pollfd *rwPolls = nullptr;

private:
    static void *middle_thread(void *param);
};

#endif //MIDDLE_MIDDLE_H
