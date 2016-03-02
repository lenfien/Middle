#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "MessageMonitor.h"
#include "Net.h"
#include "ServerManager.h"
#include "Middle.h"
#include "AuthorityManager.h"

using namespace std;
int TerminalCounter = 0;

void demonlize() {
    if (fork() != 0)
        exit(0);

    setsid();

    if (fork())
        exit(0);

    for (int index = 0; index < 125; index ++ )
        close (index);

    chdir ("/tmp");
}

time_t startTime = time(nullptr);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
void *report_middle_running(void *param) {

    int preNum = -1;
    int curNum = -1;
    char buf[256];

    while (true) {
        tm vtm;
        time_t vt = time(nullptr);
        localtime_r(&vt, &vtm);
        curNum = (int) Middle::get_middle_instance_counter();
        cout << (1900 + vtm.tm_year) << "/" << vtm.tm_mon << "/" << vtm.tm_mday << " " << vtm.tm_hour << ":" <<  vtm.tm_min << ":" << vtm.tm_sec << "\t已运行:" << (time(
                nullptr) - startTime) << "s" << "\t正在运行中的Middle:" << Middle::get_middle_instance_counter()
            << "\t使用到的Message:" <<  Message::get_use_count() << endl;
        preNum = curNum;
        timespec ts{.tv_sec = 2, .tv_nsec = 0};
        nanosleep(&ts, nullptr);
    }

    return nullptr;
}
#pragma clang diagnostic pop


int main(int argc, char **args) {
    bool debug = false;
    bool report = false;

    int err;
    struct addrinfo hints;
    struct addrinfo *result;

    struct sigaction sa;
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGSTOP, &sa, nullptr);
    sigaction(SIGPIPE, &sa, nullptr);

    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;

    /* 地址获取成功后才 */
    err = getaddrinfo(NULL, args[1], &hints, &result);
    if (err != 0) {
        system_err << gai_strerror(err) << std::endl;
        exit(1);
    }

    if (argc >= 3) {
        std::string param(args[2]);
        if (param == "-debug") {
            debug = true;
        }
    }

    if (argc >= 4) {
        std::string param(args[3]);
        if (param == "-report") {
            report = true;
        }
    }

    if (!debug)
        demonlize();
    else {
        if (report) {
            pthread_t reportThread;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
            pthread_create(&reportThread, &attr, report_middle_running, nullptr);
            pthread_attr_destroy(&attr);
        }
    }

    rlimit limit;
    err = getrlimit(RLIMIT_NOFILE, &limit);
    if (err == -1) {
        system_err << "getrlimit" << strerror(errno) << endl;
    }
    limit.rlim_max = 100000;
    limit.rlim_cur = limit.rlim_max;
    err = setrlimit(RLIMIT_NOFILE, &limit);
    if (err == -1) {
        system_err << "setrlimit" << strerror(errno) << endl;
    }
    err = getrlimit(RLIMIT_NOFILE, &limit);
    if (err == -1) {
        system_err << "getrlimit" << strerror(errno) << endl;
    }
    cout << "limit_cur:" << limit.rlim_cur << " limit_max:" << limit.rlim_max << endl;

    int bsock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if(bsock == -1) {
        system_err << strerror(errno) << std::endl;
        exit(1);
    }

    int v = 1;
    socklen_t len = sizeof(v);
    setsockopt(bsock, SOL_SOCKET, SO_REUSEADDR, &v, len);

    err = ::bind(bsock, result->ai_addr, result->ai_addrlen);
    if (err == -1) {
        system_err << "Bind fail : " << strerror(errno) << std::endl;
        exit(1);
    }

    listen(bsock, 1000);
    int loop = true;
    while(loop) {
        int clisock = accept(bsock, NULL, NULL);
        if(clisock == -1) {
            if (errno != EINTR) {
                system_err << "accept -1" << strerror(errno) << std::endl;
                loop = -1;
            }

            continue;
        }

        new Middle(clisock);
    }
}