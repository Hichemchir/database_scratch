#pragma once
#include "db/common.hpp"
#include "db/database.hpp"

namespace db {

class CLI {
public:
    void run();
    void handle_command(const string& cmd);

private:
    Database db;
};

}
