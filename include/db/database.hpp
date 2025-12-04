#pragma once
#include "common.hpp"
#include "wal.hpp"

namespace db {

class Database {
public:
    Database();

    void set(const string& key, const string& value);
    string get(const string& key) const;
    bool del(const string& key);
    bool exists(const string& key) const;

private:
    unordered_map<string, string> kv;
    WAL wal;

    void replay_wal();
};

}
