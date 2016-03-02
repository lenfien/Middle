//
// Created by lenfien on 15/11/4.
//

#ifndef MIDDLE_MESSAGEMONITOR_H
#define MIDDLE_MESSAGEMONITOR_H

#include <memory>
#include <vector>
#include <list>
#include "Message.h"

/*
 * MessageMonitor 负责处理输入的数据流,并从数据流中总结出Message,
 * 如果有多个Message在一次输入中MessageMonitor也可以处理.
 *
 * 向run方法中输入数据,当满足一个Message后,run就会返回一个size大于0的list,这个list中
 * 包含了动态分配的Message指针.
 *
 */

class MessageMonitor {
private:
    std::vector<unsigned char> mem;
    enum BorderState {
        F_FINDING_HEAD, F_FINDING_END
    };

    BorderState bStat;

public:
    MessageMonitor() : bStat(F_FINDING_HEAD) {}

    static void encode(const std::vector<uint8_t>& src, std::vector<uint8_t>& des) throw(std::logic_error);
    static void decode(const std::vector<uint8_t>& src, std::vector<uint8_t>& des) throw(std::logic_error);
public:
    std::list<std::shared_ptr<Message>> run(unsigned char *bytes, ssize_t size);
};

#endif //MIDDLE_MESSAGEMONITOR_H
