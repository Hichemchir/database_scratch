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
    if (cmd == "help") {
        std::cout << "Commands:\n";
        std::cout << " help     Show this message\n";
        std::cout << " echo <text> Print text \n";
        std::cout << " exit     Quit the program\n";
        return;
    }    

    if (cmd.rfind("echo ", 0) == 0) {
        std:: string text = cmd.substr(5);
        std::cout << text << std::endl;
        return;
    }

    std::cout << "Unkown command" << std::endl;
}