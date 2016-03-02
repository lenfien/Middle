//
// Created by lenMac on 15/12/16.
//

#ifndef MIDDLE_AUTHORITYMANAGER_H
#define MIDDLE_AUTHORITYMANAGER_H
#include <string>
#include <map>
#include <stdexcept>
#include <fstream>
#include <pthread.h>
#include <dirent.h>
#include <unistd.h>

class AtomMap {
private:
    std::map<std::string, std::string> keyValue;
    pthread_rwlock_t rwl_keyValue = PTHREAD_RWLOCK_INITIALIZER;

public:
    AtomMap() {pthread_rwlock_init(&rwl_keyValue, nullptr);}
    AtomMap(const AtomMap& a) {
        keyValue = a.keyValue;
        rwl_keyValue = PTHREAD_RWLOCK_INITIALIZER;
    }

    ~AtomMap() {
        pthread_rwlock_destroy(&rwl_keyValue);
    }

    const std::string & operator[](const std::string& key);
    bool exists(const std::string& key);
    void add(const std::string& key, const std::string& value);
    std::map<std::string, std::string> copy_key_value() {
        pthread_rwlock_rdlock(&rwl_keyValue);
        auto back = keyValue;
        pthread_rwlock_unlock(&rwl_keyValue);
        return back;
    }
};

class AuthorityManager {
private:
    std::string path;
    std::map<std::string, AtomMap> servPhoneAuthority;    //每个服务器对应的手机号和权限的键值对的键值对
    std::map<std::string, bool> dirtyMap;
    std::map<std::string, pthread_mutex_t> lockMap;

public:
    AuthorityManager(std::string path) throw(std::logic_error, std::invalid_argument);
    void load_autority(std::string name) throw (std::logic_error, std::invalid_argument);
    void save_authority(std::string name) throw (std::out_of_range, std::logic_error, std::invalid_argument);
    AtomMap &operator[](const std::string key) throw (std::out_of_range) { return servPhoneAuthority.at(key); }
};



#endif //MIDDLE_AUTHORITYMANAGER_H
