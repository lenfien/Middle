//
// Created by lenMac on 15/12/18.
//

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
#include "Message.h"
#include "Debug.h"


using namespace std;

MessageRegisterAck::MessageRegisterAck(const std::array<unsigned char, 6>& phone,
                                       const unsigned short serialNum,
                                       const unsigned short bodySerialNum,
                                       const unsigned char reason,
                                       const string & authCode):
        Message(0x8100, phone, serialNum, nullptr, nullptr),
        bodySerialNumber(bodySerialNum),
        reason(reason),
        authorityCode(authCode) {

    size_t size = sizeof(bodySerialNum) + sizeof(reason) + authCode.size();

    unsigned char body[size];

    body[0] = (unsigned char) ((bodySerialNum >> 8) & 0xFF);
    body[1] = (unsigned char) (bodySerialNum & 0xFF);
    body[2] = reason;
    std::copy(authCode.begin(), authCode.end(), &body[3]);
    set_body(body, body + size);
    update_check_code();
}

string MessageRegisterAck::to_string(bool showByte) {
    string res = Message::to_string();
    ostringstream oss;

    oss << res << ",注册:" << (uint16_t)reason
        << ",回应流水号:" << bodySerialNumber
        << ",回应鉴权号:" << authorityCode;

    return oss.str();
}

void MessageRegisterAck::set_authority_code(const string & code) {
    vector<unsigned char> nbody(get_body_bytes(), get_body_bytes() + get_body_size());
    nbody.erase(nbody.begin() + 3, nbody.end());
    nbody.insert(nbody.end(), code.begin(), code.end());
    set_body(nbody.data(), nbody.data() + nbody.size());
    update_check_code();
    authorityCode = code;
}

void MessageRegisterAck::set_authority_result(unsigned char result) {
    unsigned char *base = bytes.data() + (seperate ? 13 : 17);
    base[2] = result;
    success = (result == 0);
    update_check_code();
}

void MessageRegisterAck::set_body_serial_number(unsigned short sn) {
    unsigned char *base = bytes.data() + (seperate ? 13 : 17);
    base[1] = (unsigned char) (sn & 0xff);
    sn >>= 8;
    base[0] = (unsigned char) (sn & 0xff);
    update_check_code();
    bodySerialNumber = sn;
}

void MessageRegisterAck::parse() {
    if (get_msg_id() != 0x8100)
        throw std::logic_error("将非0x8100的消息转换为注册应答消息");

    const uint8_t *base = get_body_bytes();
    bodySerialNumber = base[0];
    bodySerialNumber <<= 8;
    bodySerialNumber |= base[1];
    success = (base[2] == 0);
    reason = base[2];

    for (int i = 3; i < get_body_size(); i ++)
        authorityCode += base[i];
}