//
// Created by lenMac on 15/12/16.
//

#include <iostream>
#include <iomanip>
#include "Message.h"
#include "MessageMonitor.h"

using namespace std;

int main() {
    MessageMonitor messageMonitor;
    vector<uint8_t> raw_data = {0x7e, 0x1, 0x2, 0x3, 0x7e, 0x7d, 0x7e, 0x7d, 0x00, 0x7d, 0x7e};
    vector<uint8_t> encoded_data = {0x7e, 0x30, 0x7d, 0x02, 0x08, 0x7d, 0x01, 0x55, 0x7e};
    vector<uint8_t> encoded_data1 = {0x7e, 0x7e};

    vector<uint8_t> res;
    messageMonitor.encode(raw_data, res);

    for (auto v : res) {
        cout  << "0x" << setw(2) << setfill('0') << hex << (uint16_t)v << " " << flush;
    }

    cout << endl;

    return 0;
}