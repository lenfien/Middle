//
// Created by lenfien on 15/12/10.
//
#include <vector>
#include <stdexcept>
#include "Debug.h"
#include "TransmitUnit.h"

using namespace std;

void TransmitUnit::set_status(Status st) {
    pthread_rwlock_wrlock(&rwl_status);
    status = st;
    pthread_rwlock_unlock(&rwl_status);
}

ssize_t TransmitUnit::send_msg(std::shared_ptr<Message> msg) {
    vector<uint8_t> encodedData;
    lastSendTime = std::time(nullptr);
    try {
        MessageMonitor::encode(msg->get_bytes(), encodedData);
        return write(sock, encodedData.data(), encodedData.size());
    }
    catch (logic_error& ler) {
        logical_err << ler.what() << endl;
    }
    return -1;
}

TransmitUnit::Status TransmitUnit::get_status() {
    Status st;
    pthread_rwlock_rdlock(&rwl_status);
    st = status;
    pthread_rwlock_unlock(&rwl_status);
    return st;
}

std::shared_ptr<Message> TransmitUnit::pop() {
    std::shared_ptr<Message> last = sendQue.front();
    sendQue.pop_front();
    if (get_queue_size() > 0) {
        int lev = static_cast<int>(sendQue.front()->get_size());
        socklen_t len = sizeof(lev);
        setsockopt(sock, SOL_SOCKET, SO_SNDLOWAT, (void *) &lev, len);
    }
    return last;
}


void TransmitUnit::push(std::shared_ptr<Message>& msg) {
    int lev;
    sendQue.push_back(msg);
    lev = static_cast<int>(sendQue.front()->get_size());
    socklen_t len = sizeof(lev);
    setsockopt(sock, SOL_SOCKET, SO_SNDLOWAT, (void*)&lev, len);
}

bool TransmitUnit::send_msg() throw (std::logic_error) {
    if (get_queue_size() == 0)
        throw std::logic_error("调用sendMsg()时, 发送队列中为空");
    return send_msg(pop()) > 0;
}
