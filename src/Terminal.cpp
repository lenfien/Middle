//
// Created by lenfien on 15/11/4.
//

#include "Terminal.h"


Terminal::Terminal(int sock) throw(std::logic_error)
        : TransmitUnit() {
    char buf[64];
    int err;
    struct sockaddr_in sockaddr;
    socklen_t len = sizeof(sockaddr);
    bzero(&sockaddr, sizeof(sockaddr));
    err = getpeername(sock, (struct sockaddr*)&sockaddr, &len);
    if (err == -1)
        throw std::logic_error("getpeername fail:");

    inet_ntop(AF_INET, &sockaddr.sin_addr, buf, sizeof(buf));
    ip = buf;
    port = ntohs(sockaddr.sin_port);
    status = CONNECTED;

    set_name("Terminal");
    this->sock = sock;
}