//
// Created by lenfien on 15/12/10.
//

#ifndef MIDDLE_TRANSMITUNIT_H
#define MIDDLE_TRANSMITUNIT_H

#include <string>
#include <list>
#include <memory>
#include <queue>
#include <deque>
#include <sstream>
#include <cstring>
#include <ctime>

#include "Debug.h"
#include "MessageMonitor.h"
#include "Message.h"
#include "Net.h"

class TransmitUnit {
public:
    enum Status {DISCONNECT, CONNECTTING, CONNECTED, FAIL};

protected:
    int sock;

    /*发送队列*/
    std::deque<std::shared_ptr<Message>> sendQue;

protected:
    MessageMonitor monitor;

protected:
    std::string name = "";
    std::string ip = "";
    in_port_t port = 0;

    Status status = DISCONNECT;
    time_t lastSendTime = 0;
    pthread_rwlock_t rwl_status = PTHREAD_RWLOCK_INITIALIZER;

protected:
    TransmitUnit() {}

    virtual ~TransmitUnit() {
        close(sock);
        pthread_rwlock_destroy(&rwl_status);
    }

public:
    void push(std::shared_ptr<Message>& msg);
    std::shared_ptr<Message> pop();
    std::shared_ptr<Message> front() {return sendQue.front();}
    std::size_t get_queue_size() {return sendQue.size();}
    ssize_t send_msg(std::shared_ptr<Message> msg);
    bool send_msg() throw (std::logic_error);

    void set_status(Status st);

    Status get_status();

    int get_sock() {return sock;}

    void set_name(const std::string &name) { TransmitUnit::name = name; }

    std::string get_name() { return name; }

    std::string get_full_name() {
        std::stringstream ss;
        ss << "[" << name << "," << ip << ":" << port << "]";
        return ss.str();
    }

    const std::string get_ip() const { return ip; }

    void set_ip(const std::string &ip) { TransmitUnit::ip = ip; }

    in_port_t get_port() const { return port; }

    void set_port(in_port_t port) { TransmitUnit::port = port; }

    time_t get_last_send_time() const { return lastSendTime; }

    MessageMonitor &get_monitor() { return monitor; }

    void clear_send_queue() { sendQue.clear(); }

    bool is_connected() {return status == CONNECTED;}
};




#endif //MIDDLE_TRANSMITUNIT_H
