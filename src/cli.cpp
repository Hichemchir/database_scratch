#include <iostream>
#include "cli.hpp"

void CLI::run() {
    std::string cmd;

    std::cout <<"Welcome to database_scratch CLI!" <<std::endl;

    while (true) {
        std::cout << "> ";

        if (!std::getline(std::cin, cmd)) {
            break;
        }
        if (cmd == "exit") {
            std::cout <<"Exiting CLI." << std::endl;
            break;
        }

        handle_command(cmd);
    }
}

void CLI::handle_command(const std::string& cmd) {
    std::cout << "You typed: " << cmd << std::endl;
}