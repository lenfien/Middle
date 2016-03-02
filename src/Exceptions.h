//
// Created by lenfien on 15/11/9.
//

#ifndef MIDDLE_EXCEPTION_H_H
#define MIDDLE_EXCEPTION_H_H

#include <exception>
#include <cerrno>
#include <cstring>

class Exception : public std::exception {
private:
    const char *msg = nullptr;
    int errn = 0;

public:
    Exception(const char *msg) :msg(msg), errn(errno) {}
    virtual const char *what() {
        if (msg)
            return msg;
        return strerror(errn);
    }

    virtual const char *errstr() {return strerror(errn);}
    virtual int errnum() {return errn;}
};


class FDException: public Exception {
public:
    FDException(const char *msg = "File Descriptor Exception"):Exception(msg) {}
};

class ServerManagerException : public Exception {
public:
    ServerManagerException(const char *msg = "Server Manager Exception"):Exception(msg) {}
};



#endif //MIDDLE_EXCEPTION_H_H
