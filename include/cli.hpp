#pragma once
#include <string>
#include "database.hpp"

class CLI {
public:
    void run();
    void handle_command(const std::string& cmd);

private:
    Database db;
};
