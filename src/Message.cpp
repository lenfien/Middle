//
// Created by lenfien on 15/12/2.
//

#include <sstream>
#include <string>
#include <array>
#include <iomanip>
#include "Debug.h"
#include "Message.h"

using namespace std;
std::string Message::to_string(bool show_bytes) {
    int i;
    ostringstream oss;
    string msgType;

    switch(get_msg_id()) {
        case 0x0102:
            msgType = "鉴权";
            break;
        case 0x0200:
            msgType = "位置";
            break;
        case 0x8100:
            msgType = "注册应答";
            break;
        case 0x0100:
            msgType = "终端注册";
            break;
        case 0x0002:
            msgType = "终端心跳";
            break;
        case 0x8001:
            msgType = "平台通用应答";
            break;
        case 0x0001:
            msgType = "终端通用应答";
            break;
        case 0x0003:
            msgType = "终端注销";
            break;
        case 0x0F02:
            msgType = "故障上传";
            break;
        case 0x0F04:
            msgType = "行为上报";
            break;
        default:
            msgType = "未知";
            break;
    }

    oss << "类型:" << msgType << ","
        << "ID:" << showbase << hex << msgId << ","
        << "长度:" << dec << bytes.size() << ","
        << "大小:" << dec << get_body_size() << ","
        << "方式:" << hex << (unsigned short)encodeType << ","
        << "分包:" << (seperate ? "是" : "否") << ","
        << "手机:" << get_phone_str() << ","
        << "流水:" << dec << serialNumber;

    if (show_bytes) {
        oss << " bytes:";
        for (i = 0; i < bytes.size(); i++) {
            oss  << noshowbase << "0x" << hex << setw(2) << setfill('0') << (0xff & (unsigned int) bytes[i]);
            if (i < bytes.size() - 1)
                oss << ",";
        }
    }

    return oss.str();
}

const std::string &Message::get_phone_str() {
    std::ostringstream oss;
    for (int i = 5; i != 11; i ++)
        oss << std::hex << std::setw(2) << std::setfill('0') <<  (unsigned short)(bytes[i]);
    phoneStr = oss.str();
    return phoneStr;
}

Message::~Message() {
    pthread_rwlock_wrlock(&rwl_count);
    count --;
    pthread_rwlock_unlock(&rwl_count);
}

Message::Message(const Message &msg) {
    pthread_rwlock_wrlock(&rwl_count);
    count ++;
    pthread_rwlock_unlock(&rwl_count);

    bytes = msg.bytes;
    msgId = msg.msgId;
    attribute = msg.attribute;
    bodySize = msg.bodySize;
    encodeType = msg.encodeType;
    phone = msg.phone;
    phoneStr = msg.phoneStr;
    serialNumber = msg.serialNumber;
    seperate = msg.seperate;
    sepSum = msg.sepSum;
    sepNum = msg.sepNum;
}


Message &Message::set_attribute(const uint16_t attr) {
    bytes[4] = (unsigned char) attr;
    bytes[3] = (unsigned char) (attr >> 8);
    attribute = attr;
    return *this;
}

Message &Message::set_body_size(const uint16_t size) {
    uint16_t oldAttr = attribute;
    oldAttr &= ~(0x1FF);
    oldAttr |= (size & 0x1FF);
    return set_attribute(oldAttr);
}

/*
 * 设置消息体, 还会设置消息头中消息体的尺寸
 * 但没有更新校验码
 * 调用这个函数后应该手动调用update_check_code来更新校验码
 */
Message &Message::set_body(const unsigned char *beg, const unsigned char *end) {
    auto bodyIt = bytes.begin() + (seperate ? 17 : 13);
    bytes.erase(bodyIt, bytes.end());
    bytes.insert(bytes.end(), beg, end);
    bytes.push_back(0x00);
    bytes.push_back(0x7e);
    set_body_size((uint16_t) (end - beg));
    return *this;
}

Message &Message::update_check_code() {
    uint8_t code = 0;
    for (auto it = bytes.begin() + 1; it != bytes.end() - 2; it ++)
        code ^= *it;

    bytes[bytes.size() - 2] = code;
    return *this;
}

size_t Message::get_use_count() {
    size_t res;
    pthread_rwlock_rdlock(&rwl_count);
    res = count;
    pthread_rwlock_unlock(&rwl_count);
    return res;
}

const unsigned char *Message::get_body_bytes() const {
    if (seperate)
        return bytes.data() + 17;
    else
        return bytes.data() + 13;
}

uint16_t Message::get_body_size() {
    attribute = 0;
    attribute |= bytes[3];
    attribute <<= 8;
    attribute |= bytes[4];
    bodySize = (uint16_t) (attribute & 0x1FF);
    return bodySize;
}

uint16_t Message::get_serial_number() {
    serialNumber = (uint16_t) (bytes[11] & 0xff);
    serialNumber <<= 8;
    serialNumber |= (bytes[12] & 0xff);
    return serialNumber;
}

void Message::parse() throw (logic_error) {
    if (bytes.size() < 13)
        goto report;

    if (bytes[0] != 0x7e || bytes.back() != 0x7e)
        goto report;

    msgId = bytes[1];
    msgId <<= 8;
    msgId |= bytes[2];

    attribute = bytes[3];
    attribute <<= 8;
    attribute |= bytes[4];

    seperate = ((attribute & (0x01 << 13)) != 0);
    encodeType = (uint8_t) ((attribute >> 10) & 0x07);
    bodySize = (uint16_t) (attribute & 0x3FF);

    if (seperate) {
        if (bytes.size() != (bodySize + 16 + 2 + 1))
            goto report;
    }
    else {
        if (bytes.size() != (bodySize + 12 + 2 + 1))
            goto report;
    }

    for (int i = 0; i < 6; i ++)
        phone[i] = bytes[5 + i];

    serialNumber = bytes[11];
    serialNumber <<= 8;
    serialNumber |= bytes[12];

    if (seperate) {
        sepSum = bytes[13];
        sepSum <<= 8;
        sepSum |= bytes[14];

        sepNum = bytes[15];
        sepNum <<= 8;
        sepNum |= bytes[16];
    }

    return;

report:
    logical_err << "解析到错误的消息包:";
    for (auto c : bytes)
        cerr << showbase << hex << (uint16_t)c << " " ;
    cerr << endl;

    throw std::logic_error("解析消息出现错误");
}


Message::Message(uint16_t msgId, const std::array<uint8_t, 6>& phone,
                 uint16_t serialNum, const uint8_t *bodyBeg, const uint8_t *bodyEnd)
        : msgId(msgId), serialNumber(serialNum), phone(phone), seperate(false) {

    attribute = 0;
    attribute |= ((bodyEnd - bodyBeg) & 0x1FF);

    bytes.push_back(0x7e);
    bytes.push_back((unsigned char) ((msgId >> 8) & 0xFF));
    bytes.push_back((unsigned char) (msgId & 0xFF));
    bytes.push_back((unsigned char) ((attribute >> 8) & 0xFF));
    bytes.push_back((unsigned char) (attribute & 0xFF));
    for (int i = 3; i != 10; i ++)
        bytes.push_back(phone[i - 3]);

    bytes.push_back((unsigned char) ((serialNum >> 8) & 0xFF));
    bytes.push_back((unsigned char) (serialNum & 0xFF));

    bytes.insert(bytes.end(), bodyBeg, bodyEnd);
    bytes.push_back(0x00);
    bytes.push_back(0x7e);
}

Message::Message(const uint8_t * beg, const uint8_t * end) : bytes(beg, end) {

    parse();

    pthread_rwlock_wrlock(&rwl_count);
    count ++;
    pthread_rwlock_unlock(&rwl_count);
}

void AuthorityMessage::parse() {
    if (get_msg_id() != 0x0102)
        throw std::logic_error("将非0x0102的消息转换为终端鉴权消息");

    authorityCode = "";
    for (auto it = body_begin(); it != body_end(); it ++ )
        authorityCode += *it;
}