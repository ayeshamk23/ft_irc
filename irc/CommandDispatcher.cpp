#include "CommandDispatcher.hpp"
#include "Client.hpp"  // Make sure the filename matches exactly
#include <sstream>
#include <iostream>

// Constructor: Register commands
CommandDispatcher::CommandDispatcher() {
    registerCommand("NICK", &CommandDispatcher::handleNick);
    registerCommand("USER", &CommandDispatcher::handleUser);
    registerCommand("PASS", &CommandDispatcher::handlePass);
    registerCommand("PING", &CommandDispatcher::handlePing);
    registerCommand("PONG", &CommandDispatcher::handlePong);
    registerCommand("QUIT", &CommandDispatcher::handleQuit);
}

// Register command handler
void CommandDispatcher::registerCommand(const std::string& command, CommandHandler handler) {
    commandHandlers[command] = handler;
}

// Dispatch commands from input string (can have multiple commands separated by newlines)
void CommandDispatcher::dispatchCommand(Client& client, const std::string& input) {
    std::istringstream stream(input);
    std::string line;

    while (std::getline(stream, line)) {
        if (line.empty())
            continue;

        std::vector<std::string> tokens = split(line);
        if (tokens.empty())
            continue;

        std::string command = tokens[0];
        tokens.erase(tokens.begin()); // Remove command from args

        std::map<std::string, CommandHandler>::iterator it = commandHandlers.find(command);
        if (it != commandHandlers.end()) {
            CommandHandler handler = it->second;
            handler(client, tokens);
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }
}

// Helper: split string by whitespace
std::vector<std::string> CommandDispatcher::split(const std::string& line) {
    std::istringstream ss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (ss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// ===== Command Handlers =====

// Use (void) to avoid unused parameter warnings/errors
void CommandDispatcher::handleNick(Client& client, const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Error: NICK command requires a nickname" << std::endl;
        return;
    }
    client.setNickname(args[0]);
    std::cout << "Nickname set to: " << client.getNickname() << std::endl;
}

void CommandDispatcher::handleUser(Client& client, const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Error: USER command requires a username" << std::endl;
        return;
    }
    client.setUsername(args[0]);
    std::cout << "Username set to: " << client.getUsername() << std::endl;
}

void CommandDispatcher::handlePass(Client& client, const std::vector<std::string>& args) {
    if (args.empty()) {
        std::cout << "Error: PASS command requires a password" << std::endl;
        return;
    }
    const std::string serverPassword = "mypassword"; // change to your real server password

    if (args[0] == serverPassword) {
        client.authenticate();
        std::cout << "Authentication successful." << std::endl;
    } else {
        std::cout << "Authentication failed. Wrong password." << std::endl;
    }
}

void CommandDispatcher::handlePing(Client& client, const std::vector<std::string>& args) {
    (void)client;
    (void)args;
    std::cout << "Handling PING command" << std::endl;
}

void CommandDispatcher::handlePong(Client& client, const std::vector<std::string>& args) {
    (void)client;
    (void)args;
    std::cout << "Handling PONG command" << std::endl;
}

void CommandDispatcher::handleQuit(Client& client, const std::vector<std::string>& args) {
    (void)client;
    (void)args;
    std::cout << "Handling QUIT command" << std::endl;
}
