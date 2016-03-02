//
// Created by lenfien on 15/11/4.
//

#include <memory>
#include <list>

#include "Net.h"
#include "Message.h"
#include "MessageMonitor.h"

using namespace std;

pthread_rwlock_t Message::rwl_count = PTHREAD_RWLOCK_INITIALIZER;
size_t Message::count = 0;

std::list<std::shared_ptr<Message>> MessageMonitor::run(unsigned char *bytes, ssize_t size) {
    std::list<std::shared_ptr<Message>> result;
    vector<uint8_t> decodedMem;

    for (int i = 0; i < size; i ++ ) {
        if(bytes[i]  == 0x7e) {
            if(this->bStat == F_FINDING_HEAD) {
                this->bStat = F_FINDING_END;
            }
            else {
                mem.push_back(bytes[i]);

                try {
                    decodedMem.clear();
                    decode(mem, decodedMem);

                    if (decodedMem.size() < 4)
                        throw logic_error("获取到一个长度<4的消息");

                    uint16_t msgId = 0;
                    msgId = decodedMem[1];
                    msgId <<= 8;
                    msgId |= decodedMem[2];

                    shared_ptr<Message> msg;
                    switch (msgId) {
                        case 0x0102:
                            msg.reset(new AuthorityMessage(decodedMem.data(), decodedMem.data() + decodedMem.size()));
                            break;

                        case 0x8100:
                            msg.reset(new MessageRegisterAck(decodedMem.data(), decodedMem.data() + decodedMem.size()));
                            break;

                        case 0x0100:
                            msg.reset(new RegisterMessage(decodedMem.data(), decodedMem.data() + decodedMem.size()));
                            break;

                        default:
                            msg.reset(new Message(decodedMem.data(), decodedMem.data() + decodedMem.size()));
                            break;
                    }
                    result.push_back(msg);
                }
                catch (logic_error& le) {
                    logical_err << le.what() << endl;
                }

                decodedMem.clear();
                mem.clear();
                this->bStat = F_FINDING_HEAD;
            }
        }
        else if (this->bStat == F_FINDING_HEAD) {
            logical_err << "发现0x7e外的数据:" << "0x" << std::hex << (0xff & (unsigned int)bytes[i]) << ", ASC:" << bytes[i] << endl;
        }

        if (this->bStat == F_FINDING_END)
            mem.push_back(bytes[i]);
    }

    return result;
}

void MessageMonitor::encode(const std::vector<uint8_t>& src, std::vector<uint8_t>& des) throw (logic_error) {
    if (src.size() < 2)
        throw logic_error("编码出错, 消息长度 < 2");

    if(src.front() != 0x7e && src.front() != src.back())
        throw logic_error("编码出错,消息不以0x7e开头或结尾");

    des.push_back(0x7e);
    for (auto srcIt = src.begin() + 1; srcIt != src.end() - 1; ++srcIt) {
        if (*srcIt == 0x7e) {
            des.push_back(0x7d);
            des.push_back(0x02);
        }
        else if (*srcIt == 0x7d) {
            des.push_back(0x7d);
            des.push_back(0x01);
        }
        else
            des.push_back(*srcIt);
    }
    des.push_back(0x7e);
}


/*
 * 解码一个消息
 *
 * src应该是以0x7e开头和结尾
 * 解码会将0x7d 0x02 转换为0x7e
 * 解码会将0x7d 0x01 转换为0x7d
 *
 * 最终的结果放入des中
 * des也是以0x7e开头和结尾
 */
void MessageMonitor::decode(const std::vector<uint8_t>& src, std::vector<uint8_t>& des) throw (logic_error) {
    if (src.size() < 2)
        throw logic_error ("解码出错, size < 2");

    if (src.front() != 0x7e && src.front() != src.back())
        throw logic_error("编码出错, 消息不以0x7e开头或结尾");

    if (src[src.size() - 2] == 0x7d)
        throw logic_error("解码出错, 消息内容最后一个字节是0x7d");

    des.push_back(0x7e);
    for (auto srcIt = src.begin() + 1; srcIt < src.end() - 1; ++srcIt) {
        if (*srcIt == 0x7d) {
            ++srcIt;
            if (*srcIt == 0x02)
                des.push_back(0x7e);
            else if (*srcIt == 0x01)
                des.push_back(0x7d);
            else
                throw logic_error("解码时出错,因为在0x7d后发现非0x01和0x02的字节");
        }
        else if (*srcIt == 0x7e)
            throw logic_error("解码时出错,因为在消息体中发现0x7e");
        else
            des.push_back(*srcIt);
    }
    des.push_back(0x7e);
}