//
// Created by lenfien on 15/11/4.
//

#ifndef MIDDLE_MESSAGE_H
#define MIDDLE_MESSAGE_H

#include <sstream>
#include <cctype>
#include <iterator>
#include <string>
#include <stdexcept>
#include <memory>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <array>
#include "Debug.h"

class Message {
private:
    static pthread_rwlock_t rwl_count;
    static size_t count;

public:
    static size_t get_use_count();

protected:
    std::vector<unsigned char> bytes;

    uint16_t msgId = 0;             //消息id
    uint16_t attribute = 0;         //消息体属性
    uint16_t bodySize = 0;          //消息体大小
    uint8_t encodeType = 0;         //加密方式
    bool seperate = false;          //是否分包
    std::array<uint8_t, 6> phone;   //手机号
    std::string phoneStr;           //字符串手机号
    uint16_t serialNumber = 0;      //流水号

    uint16_t sepSum = 0;    //分包总个数
    uint16_t sepNum = 0;    //分包中的第几个包

private:
    void parse() throw (std::logic_error);

public:
    Message(const uint8_t * beg, const uint8_t * end);

    Message(uint16_t msgId,
            const std::array<uint8_t, 6>& phone,
            uint16_t serialNum,
            const uint8_t *bodyBeg,
            const uint8_t *bodyEnd);

    Message(const Message &msg);
    virtual ~Message();

public:
    const unsigned char *body_begin() {return get_body_bytes();}
    const unsigned char *body_end() {return body_begin() + get_body_size();}

protected:
    const unsigned char *
            get_body_bytes() const;
    uint16_t
            get_body_size();

    Message &
            set_attribute(const uint16_t attr);

    Message &
            set_body_size(const uint16_t size);

    Message &
            set_body(const unsigned char *beg, const unsigned char *end);

public:
    Message &
            update_check_code();

    const std::string &
            get_phone_str();

    virtual std::string
            to_string(bool show_bytes = false);

    uint16_t
            get_msg_id() const { return msgId; }

    const std::vector<uint8_t>&
            get_bytes() const {return bytes;}

    size_t get_size() const
            { return bytes.size(); }

    uint8_t get_encode_type() const { return encodeType; }

    bool is_seperated() const { return seperate; }

    const std::array<uint8_t, 6> &get_phone() const { return phone; }

    uint16_t get_serial_number();

    uint16_t get_seperate_sum() const { return sepSum; }

    uint16_t get_seperate_number() const { return sepNum; }
};

class RegisterMessage : public Message {
private:
    void parse() {
        if (get_msg_id() != 0x0100)
            throw std::logic_error("将非0x0100的消息转换为注册消息");
    }

public:
    RegisterMessage(const Message& msg):Message(msg) { parse(); }
    RegisterMessage(const uint8_t *beg, const uint8_t* end):Message(beg, end) { parse(); }
};

class AuthorityMessage: public Message {
private:
    std::string authorityCode;

private:
    void parse();

public:
    AuthorityMessage(const Message &msg):Message(msg) { parse(); }
    AuthorityMessage(const uint8_t* beg, const uint8_t* end) : Message(beg, end) { parse(); }
    AuthorityMessage(const std::array<uint8_t, 6>& phone, uint16_t serialNum, const std::string authCode)
            :Message(0x0102, phone, serialNum,
                     (const uint8_t *) authCode.data(), (const uint8_t *) (authCode.data() + authCode.size())),
             authorityCode(authCode) {
    }

    std::string get_authority_code() { return authorityCode; }
    void set_authority_code(const std::string& code) {
        set_body((const unsigned char *) code.data(), (const unsigned char *) (code.data() + code.size()));
        update_check_code();
        authorityCode = code;
    }

    virtual std::string to_string (bool showBytes = false) {
        std::string header = Message::to_string();
        header += ",鉴权码:";
        header +=  authorityCode;

        return header;
    }
};

/* 注册应答消息 */
class MessageRegisterAck : public Message {
private:
    const unsigned char *base = nullptr;  //消息体起始字节
    bool success = false;
    unsigned char reason = 0;
    uint16_t bodySerialNumber;
    std::string authorityCode;

public:
    MessageRegisterAck(const Message& m) : Message(m) { parse(); }
    MessageRegisterAck(const uint8_t* beg, const uint8_t* end) : Message(beg, end) { parse(); }
    MessageRegisterAck(const std::array<uint8_t, 6>& phone,
                       const uint16_t serialNum,
                       const uint16_t bodySerialNum,
                       const uint8_t reason,
                       const std::string& authCode);

private:
    void parse();

public:
    uint16_t get_body_serial_number() const { return bodySerialNumber; }
    const std::string &get_authority_code() const { return authorityCode; }

    void    set_authority_code(const std::string& code);
    void    set_authority_result(uint8_t result);
    void    set_body_serial_number(uint16_t sn);

    bool is_success() const { return success; }
    unsigned char get_reason() const { return reason; }

    virtual std::string to_string(bool showByte = false);
};

#endif //MIDDLE_MESSAGE_H
