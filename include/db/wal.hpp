#include "common.hpp"
#include <fstream>

namespace db {

enum class WalOp: uint8_t {
    SET = 1,
    DEL = 2
};

class WAL {
public:
    WAL(const string& filename);
    // close file
    ~WAL();

    void write_set(const string& key, const string& value);
    void write_del(const string& key);

    struct Record {
        WalOp op;
        string key;
        string value;
        bool valid;
    };

    vector<Record> read_all();

private:
    string filename;
    std::ofstream out;

    void write_record(WalOp op, const string& key, const string& value);
    uint32_t crc32(const char *data, size_t size);
};

}