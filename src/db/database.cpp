#include "database.hpp"
using namespace std;

void Database::set(const string& key, const string& value) {
    storage[key] = value;
};

string Database::get(const string& key) const {
    auto it = storage.find(key);
    if (it != storage.end()) {
        return it->second;
    }
    return "";
}

bool Database::del(const string& key) {
    return storage.erase(key) > 0;
}

bool Database::exists(const string& key) {
    return (storage.find(key)) == storage.end();
}