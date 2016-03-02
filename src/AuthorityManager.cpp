//
// Created by lenMac on 15/12/16.
//

#include <iostream>
#include <sstream>
#include "AuthorityManager.h"
#include "Debug.h"
using namespace std;

void AuthorityManager::load_autority(std::string name) throw (logic_error, invalid_argument) {
    if (chdir(path.c_str()) == -1)
        throw invalid_argument(std::string("chdir 到") + path + "失败");

    AtomMap keyValue;
    istringstream iss;
    std::ifstream ifs(name);
    if (!ifs)
        throw std::invalid_argument((std::string("读取鉴权表时出错: 打开文件失败, ") + name).c_str());

    std::string line;
    std::string key, value;
    while (getline(ifs, line)) {
        if (line.size() == 0 || line[0] == '#')
            continue;

        iss.str(line);
        iss.clear();
        iss >> key >> value;
        if (iss.fail())
            throw std::logic_error(std::string("读取鉴权表是出错") + name + " " + line + " " + key + " " + value);

        keyValue.add(key, value);
    }

    servPhoneAuthority.insert(make_pair(name, keyValue));
    lockMap[name] = PTHREAD_MUTEX_INITIALIZER;
}

AuthorityManager::AuthorityManager(std::string path) throw (logic_error, invalid_argument)
        :path(path)
{
    if (chdir(path.c_str()) == -1)
        throw invalid_argument(std::string("chdir 到") + path + "失败");

    DIR* dir = opendir(path.c_str());
    if (dir == nullptr)
        throw std::logic_error(string("打开文件夹失败") + path.c_str());

    dirent *ent;
    while ((ent = readdir(dir)) != nullptr) {
        string fileName(ent->d_name);
        if (fileName == "." || fileName == ".." || fileName[0] == '.')
            continue;

        load_autority(fileName);
    }

    for (auto &v : servPhoneAuthority) {
        cout << v.first << ":" << endl;
        auto kv = v.second.copy_key_value();
        for (auto &vv :kv ) {
            cout << "\t" << vv.first << " " << vv.second << endl;
        }
    }
}

void AuthorityManager::save_authority(std::string name) throw (std::out_of_range, std::logic_error, std::invalid_argument) {
    if (chdir(path.c_str()) == -1)
        throw invalid_argument(std::string("chdir 到") + path + "失败");

    pthread_mutex_t &lock = lockMap.at(name);
    pthread_mutex_lock(&lock);

    fstream ofs(name, ios_base::trunc | ios_base::out);
    if (!ofs) {
        pthread_mutex_unlock(&lock);
        throw logic_error(std::string("保存鉴权表失败, 打开文件失败") + name);
    }

    auto kv = servPhoneAuthority[name].copy_key_value();
    for (auto &p : kv)
        ofs << p.first << "\t" << p.second << endl;

    ofs.close();

    pthread_mutex_unlock(&lock);
}

bool AtomMap::exists(const std::string& key) {
    bool exist;
    pthread_rwlock_rdlock(&rwl_keyValue);
    exist = (keyValue.find(key) != keyValue.end());
    pthread_rwlock_unlock(&rwl_keyValue);
    return exist;
}

const std::string &AtomMap::operator[](const std::string& key) {
    pthread_rwlock_rdlock(&rwl_keyValue);
    const std::string& value = keyValue[key];
    pthread_rwlock_unlock(&rwl_keyValue);
    return value;
}

void AtomMap::add(const std::string& key, const std::string& value) {
    pthread_rwlock_wrlock(&rwl_keyValue);
    keyValue[key] = value;
    pthread_rwlock_unlock(&rwl_keyValue);
}