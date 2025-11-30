#include "db/kv_store.hpp"

namespace db {

void set(const string& key, const string& value) {
    store[key] = value;
}

string get(const string& key, const string& out_value) {
    auto it = store.find(key);
    if (it != store.end()) {
        out_value = it->second;
        return true;
    }
    return false;
}

bool del(const string& key) {
    return store.erase(key) > 0;
}

bool exists(const string& key) {
    return (store.find(key)) != store.end();
}

}