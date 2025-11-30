#include "db/database.hpp"

namespace db {

void Database::set(const string& key, const string& value) {
    store.set(key,value);
};

string Database::get(const string& key) const {
    string value;
    if (store.get(key, value)) {
        return value;
    }
    return "";
}

bool Database::del(const string& key) {
    return store.del(key);
}

bool Database::exists(const string& key) {
    return store.exists(key);
}

}