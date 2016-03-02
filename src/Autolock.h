//
// Created by lenMac on 15/12/19.
//

#ifndef MIDDLE_AUTOLOCK_H
#define MIDDLE_AUTOLOCK_H

#include <pthread.h>
#include <stdexcept>

class AutoMutex {
private:
    bool locked = false;
    pthread_mutex_t& mutex;

public:
    AutoMutex(pthread_mutex_t& mutex):mutex(mutex) {}
    ~AutoMutex() {
        if (locked)
            pthread_mutex_unlock(&mutex);
    }

    void lock() {
        if (locked)
            throw std::logic_error("在同一个AutoMutex重复加锁");

        pthread_mutex_lock(&mutex);
        locked = true;
    }

    void unlock() {
        if (locked) {
            pthread_mutex_unlock(&mutex);
            locked = false;
        }
        else
            throw std::logic_error("在AutoMutex中解锁未加锁的Mutex");
    }

private:
    AutoMutex(const AutoMutex& mtx) = default;
};


class AutoRwlock {
private:
    bool locked = false;
    pthread_rwlock_t& wrlock;

public:
    AutoRwlock(pthread_rwlock_t& wrlock):wrlock(wrlock) {}
    ~AutoRwlock() {
        if (locked)
            pthread_rwlock_unlock(&wrlock);
    }

    void wlock() {
        if (locked)
            throw std::logic_error("在同一个AutoRwlock重复加锁");

        pthread_rwlock_wrlock(&wrlock);
        locked = true;
    }

    void rdlock() {
        if (locked)
            throw std::logic_error("在同一个AutoRwlock重复加锁");

        pthread_rwlock_rdlock(&wrlock);
        locked = true;
    }

    void unlock() {
        if (locked) {
            pthread_rwlock_unlock(&wrlock);
            locked = false;
        }
        else
            throw std::logic_error("在AutoRwlock中解锁未加锁的rwlock");
    }

private:
    AutoRwlock(const AutoRwlock& mtx) = default;
};

#endif //MIDDLE_AUTOLOCK_H
