#pragma once
#include "common.hpp"

namespace db {

class Database {
public:
    // Insert or replace key
    void set(const string& key, const string& value);

    // Return value associated to key
    string get(const string& key) const;

    // Delete key
    bool del(const string& key);

    // Check if key exists
    bool exists(const string& key);

private:
    unordered_map<string, string> storage;
};

}