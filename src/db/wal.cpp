#include "db/wal.hpp"
#include <fstream>
#include <vector>
#include <cstring>

namespace db {

WAL::WAL(const string& filename)
    : filename(filename), out(filename, std::ios::binary | std::ios::app)
{
}  

WAL::~WAL() {
    // force write data from buffer to disk
    // nothin in memory
    out.flush();
    out.close();
}


uint32_t WAL::crc32(const char *data, size_t size) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < size; ++i) {
        crc ^= (uint8_t)data[i]; // XOR
        for (int j = 0; j < 8; j++) {
            crc = (crc >> 1) ^ (0xEDB88320 & -(crc & 1)); // bit shift to right (similar to //2) & XOR conditional
        }
    }
    return ~crc;
}


void WAL::write_record(WalOp op, const string& key, const string &value) {
    uint32_t key_len = key.size();
    uint32_t val_len = value.size();

    // prepare buffer
    vector <char> buf;
    buf.reserve(1 + 4 + 4 + key_len + val_len);
    buf.push_back(static_cast<uint8_t>(op));
    buf.insert(buf.end(), (char *)&key_len, (char *)&key_len + 4);
    buf.insert(buf.end(), (char *)&val_len, (char *)&val_len + 4);

    buf.insert(buf.end(), key.begin(), key.end());
    buf.insert(buf.end(), value.begin(), value.end());

    // compute CRC
    uint32_t crc = crc32(buf.data(), buf.size());

    // write CRC + buffer
    out.write((char *)&crc, 4);
    out.write(buf.data(), buf.size());
    out.flush();
}

void WAL::write_set(const string& key, const string& value) {
    write_record(WalOp::SET, key, value);
}

void WAL::write_del(const string& key) {
    write_record(WalOp::DEL, key, "");
}

vector<WAL::Record> WAL::read_all() {
    vector<Record> records;
    std::ifstream in(filename, std::ios::binary);

    while (true) {
        uint32_t crc;
        if (!in.read((char *)&crc, 4)) break;

        uint8_t op;
        uint32_t key_len;
        uint32_t val_len;

        if (!in.read((char *)&op, 1)) break;
        if (!in.read((char *)&key_len, 4)) break;
        if (!in.read((char *)&val_len, 4)) break;

        vector<char> key(key_len);
        vector<char> val(val_len);

        if (!in.read(key.data(), key_len)) break;
        if (!in.read(val.data(), val_len)) break;

        vector<char> tmp;
        tmp.push_back(op);
        tmp.insert(tmp.end(), (char *)&key_len, (char *)&key_len + 4);
        tmp.insert(tmp.end(), (char *)&val_len, (char *)&val_len + 4);
        tmp.insert(tmp.end(), key.begin(), key.end());
        tmp.insert(tmp.end(), val.begin(), val.end());

        // calculate crc
        uint32_t computed = crc32(tmp.data(), tmp.size());

        // check if valid record or corrupted
        bool valid = (computed == crc);

        records.push_back({
            (WalOp)op,
            string(key.begin(), key.end()),
            string(val.begin(), val.end()),
            valid
        }
        );
    }
    return records;
}



}