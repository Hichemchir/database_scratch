#pragma once
#include <string>
#include <unordered_map>

class Database {
public:
    // Insert or replace key
    void set(const std::string& key, const std::string& value);

    // Return value associated to key
    std::string get(const std::string& key) const;

    // Delete key
    bool del(const std::string& key);

    // Check if key exists
    bool exists(const std::string& key);

private:
    std::unordered_map<std::string, std::string> storage;
};