#include <iostream>
#include <sstream>

#include "db/common.hpp"
#include "db/database.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::istringstream;
using std::getline;

namespace db {

void CLI::run() {
    string cmd;

    cout <<"Welcome to database_scratch CLI!" << endl;

    while (true) {
        cout << "> ";

        if (!getline(cin, cmd)) {
            break;
        }
        if (cmd == "exit") {
            cout <<"Exiting CLI." << endl;
            break;
        }

        handle_command(cmd);
    }
}

void CLI::handle_command(const string& cmd) {
    istringstream iss(cmd);
    vector<string> tokens;
    string word;

    while (iss >> word) {
        tokens.push_back(word);
    }
    if (tokens.empty()) return;

    const string& command = tokens[0];

    if (command == "help") {
        cout << "Commands:\n";
        cout << " help     Show this message\n";
        cout << " echo <text> Print text \n";
        cout << " clear    Clean the program\n";
        cout << " exit     Quit the program\n";
        cout << " set     Setup key, value for database\n";
        cout << " get     Value for the key\n";
        cout << " exists     Check if key exists\n";
        cout << " del     Delete the key\n";

        return;
    }    

    if (command == "echo") {
        if (tokens.size() > 1) {
            for (size_t i = 1; i < tokens.size(); i++) {
                cout << tokens[i] << " ";
            }
            cout << endl;
        }
        return;
    }

    if (command == "clear") {
        cout << "\033[2J\033[1;1H";
        return;
    }

    if (command == "set") {
        if (tokens.size() < 3) {
            cout << "Usage: <key> <value>\n";
            return;
        }
        db.set(tokens[1], tokens[2]);
        cout << "OK\n";
        return;
    }

    if (command == "get") {
        if (tokens.size() < 2) {
            cout << "Usage: get <key>\n";
            return;
        }
        cout << db.get(tokens[1]) << endl;
        return;
    }

    if (command == "del") {
        if (tokens.size() < 2) {
            cout << "Usage: del <key>\n";
            return;
        }
        cout << (db.del(tokens[1]) ? "1" : "0") << endl;
        return;
    }

    if (command == "exists") {
        if (tokens.size() < 2) {
            cout << "Usage: exists <key>\n";
            return;
        }
        cout << db.exists(tokens[1]) << endl;
        return;
    }

    cout << "Unknown command" << endl;
}
}