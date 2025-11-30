#pragma once
#include <string>

class CLI {
public:
    void run();
    void handle_command(const std::string& cmd);
};
