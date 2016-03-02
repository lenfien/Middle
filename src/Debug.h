//
// Created by lenfien on 15/11/4.
//

#ifndef MIDDLE_DEBUG_H_H
#define MIDDLE_DEBUG_H_H

#include <iostream>
#include <string>
#include <ctime>
#include <sys/time.h>

#define system_err      std::cerr << "[SYSERR " << get_system_time() << " " << __FUNCTION__ << "," << std::dec << __LINE__ <<  "]:"
#define logical_err     std::cerr << "[LOGERR " <<  get_system_time() << " "  << __FUNCTION__ << std::dec << "," << __LINE__ << "]:"
#define sys_log         std::cout << "[LOG " << get_system_time() << " " << __FUNCTION__ << "," << std::dec << __LINE__ << "]:"

#define location        std::cout << __FUNCTION__ << __LINE__ << std::endl

static const char *server_path = "/etc/middle";

static std::string get_system_time() {
    std::string str;
    tm ltm;
    time_t t;
    time(&t);
    localtime_r(&t, &ltm);

    str += std::to_string(ltm.tm_year + 1900);
    str += "/";
    str += std::to_string(ltm.tm_mon);
    str += "/";
    str += std::to_string(ltm.tm_mday);
    str += " ";
    str += std::to_string(ltm.tm_hour);
    str += ":";
    str += std::to_string(ltm.tm_min);
    str += ":";
    str += std::to_string(ltm.tm_sec);

    return str;
}

#endif //MIDDLE_DEBUG_H_H
