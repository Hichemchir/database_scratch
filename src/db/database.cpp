#include "db/database.hpp"
#include <sstream>

namespace db {

Database::Database()
    : storage("data.db")
{
    load_from_disk();
}

void Database::load_from_disk() {
    auto lines = storage.load_lines();

    for (const auto &line : lines) {
        std::istringstream iss(line);
        string op, key, value;
        iss >> op;

        if (op == "SET") {
            iss >> key >> value;
            kv[key] = value;
        } else if (op == "DEL") {
            iss >> key;
            kv.erase(key);
        }
    }
}

void Database::set(const string &key, const string &value) {
    kv[key] = value;
    storage.append_set(key, value);
}

string Database::get(const string &key) const {
    auto it = kv.find(key);
    return (it != kv.end()) ? it->second : "";
}

bool Database::del(const string &key) {
    auto it = kv.find(key);
    if (it == kv.end()) return false;

    kv.erase(it);
    storage.append_del(key);
    return true;
}

bool Database::exists(const string &key) {
    return kv.find(key) != kv.end();
}

} 
