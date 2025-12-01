#pragma once

#include "common.hpp"
#include <fstream>

namespace db {

class Storage {
public: 
    Storage(const string &filename);
    ~Storage();

    void append_set(const string &key, const string &value);
    void append_del(const string &key);

    vector<string> load_lines();
private:
    string filename;
    std::ofstream file;
};

}