#include "db/database.hpp"
#include <sstream>

namespace db {

Database::Database()
    : wal("wal.log")
{
    replay_wal();
}

void Database::replay_wal() {
    auto records = wal.read_all();

    for (auto &rec : records) {
        if (!rec.valid)
            continue;

        if (rec.op == WalOp::SET) {
            kv[rec.key] = rec.value;
        } 
        else if (rec.op == WalOp::DEL) {
            kv.erase(rec.key);
        }
    }
}

void Database::set(const string &key, const string &value) {
    kv[key] = value;
    wal.write_set(key, value);
}

bool Database::del(const string &key) {
    auto it = kv.find(key);
    if (it == kv.end()) return false;

    kv.erase(it);
    wal.write_del(key);
    return true;
}

string Database::get(const string &key) const {
    auto it = kv.find(key);
    return (it != kv.end()) ? it->second : "";
}

bool Database::exists(const string &key) const {
    return kv.find(key) != kv.end();
}

} 
