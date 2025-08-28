#ifndef COMMAND_DISPATCHER_HPP
#define COMMAND_DISPATCHER_HPP

#include <string>
#include <map>
#include <vector>

class Client;  // Forward declaration

typedef void (*CommandHandler)(Client&, const std::vector<std::string>&);

class CommandDispatcher {
public:
    CommandDispatcher();
    void dispatchCommand(Client& client, const std::string& input);
    void registerCommand(const std::string& command, CommandHandler handler);

private:
    std::map<std::string, CommandHandler> commandHandlers;

    std::vector<std::string> split(const std::string& line);

    // Static handler functions for commands
    static void handleNick(Client& client, const std::vector<std::string>& args);
    static void handleUser(Client& client, const std::vector<std::string>& args);
    static void handlePass(Client& client, const std::vector<std::string>& args);
    static void handlePing(Client& client, const std::vector<std::string>& args);
    static void handlePong(Client& client, const std::vector<std::string>& args);
    static void handleQuit(Client& client, const std::vector<std::string>& args);
};

#endif
