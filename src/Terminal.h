//
// Created by lenfien on 15/11/4.
//

#ifndef MIDDLE_TERMINAL_H
#define MIDDLE_TERMINAL_H

#include <string>
#include <list>
#include <memory>
#include <queue>
#include <deque>
#include <sstream>
#include <cstring>
#include <exception>
#include <stdexcept>

#include "TransmitUnit.h"
#include "Debug.h"
#include "MessageMonitor.h"
#include "Message.h"
#include "Net.h"

class Terminal: public TransmitUnit {
    friend class Middle;

public:
    Terminal(int sock) throw(std::logic_error);
};


#endif //MIDDLE_TERMINAL_H
