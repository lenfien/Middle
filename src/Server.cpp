//
// Created by lenfien on 15/11/6.
//
#include <fstream>
#include <ctime>
#include <unistd.h>
#include <stdexcept>
#include "Server.h"

using namespace std;


Server::Server() throw (FDException) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        system_err << "socket create fail" << std::endl;
        throw FDException("Socket create fail!");
    }
}

bool Server::connect_to(bool block) {
    if(!block) {
        oldFlag = fcntl(sock, F_GETFL, 0);
        fcntl(sock, F_SETFL, oldFlag | O_NONBLOCK);
    }

    struct addrinfo hints;
    bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *result;
    int err = getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &result);
    if(err != 0) {
        system_err << "Get " << ip << ":" << port << ", addr fail:" << gai_strerror(err) << std::endl;
        return false;
    }

    err = connect (sock, result->ai_addr, result->ai_addrlen);
    freeaddrinfo(result);

    if (err == 0)
        return true;

    if(err == -1 && errno != EINPROGRESS && !block) {
        system_err << "connect unblock execute, but errno is not EINPROGRESS:" << std::strerror(errno) << sock << std::endl;
        return  false;
    }

    return false;
}


Server::Server(const Server &serv) throw (logic_error, FDException)
        : Server() {
    name = serv.name;
    ip = serv.ip;
    port = serv.port;
}

