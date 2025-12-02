#pragma once

#include "common.hpp"
#include <fstream>

namespace db {

class Storage {
public:
    // constructor that opens the file
    Storage(const string &filename);
    // delete the open file, liberate ressources
    ~Storage();

    void append_set(const string &key, const string &value);
    void append_del(const string &key);

    vector<string> load_lines();
private:
    string filename;
    // open file in append mode
    std::ofstream file;
};

}