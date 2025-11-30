#pragma once
#include "common.hpp"

namespace db {

class KVStore {
public:
    KVStore() = default;

    void set(const string& key, const string& value);
    string get(const string& key, const string& out_value) const;
    bool del(const string& key);
    bool exists(const string& key) const;

private:
    unordered_map<string, string> store;
};

}