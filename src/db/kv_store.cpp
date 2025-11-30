#include "db/kv_store.hpp"

namespace db {

void KVStore::set(const string& key, const string& value) {
    store[key] = value;
}

bool KVStore::get(const string& key, string& out_value) const {
    auto it = store.find(key);
    if (it != store.end()) {
        out_value = it->second;
        return true;
    }
    return false;
}

bool KVStore::del(const string& key) {
    return store.erase(key) > 0;
}

bool KVStore::exists(const string& key) const {
    return (store.find(key)) != store.end();
}

}