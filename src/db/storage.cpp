#include "db/storage.hpp"

namespace db {

Storage::Storage(const string &filename)
    : filename(filename), file(filename, std::ios::app)
{
    // std::ios::app => always append, never overwrite
}    

Storage::~Storage() {
    file.close();
}

void Storage::append_set(const string &key, const string &value) {
    file << "SET " << key << " " << value << "\n";
    file.flush();
}
void Storage::append_del(const string &key) {
    file << "DEL " << key << "\n";
    file.flush();
}

vector<string> Storage::load_lines() {
    vector<string> lines;
    std::ifstream in(filename);

    string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    return lines;
}

}