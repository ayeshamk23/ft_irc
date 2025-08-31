
#include <string>
#include "parser.hpp"
void Server::
(std::string msg, int fd)
{
    if(send(fd, msg.c_str(), msg.size(), 0 ) == -1)
        std::cerr << "REsponse sending failed" << std::endl;
}

std::vector<std::string> Server::splitter(std::string& cmd)
{
    std::vector<std::string> vec;
    std::istringstream stm(cmd);
    std::string token;

    while(stm >> token)
    {
        vec.push_back(token);
        token.clear();
    }
    return vec;
}
void parse(std::string cmd, int fd)
{
    if(cmd.empty())
        return;
    std::vector<std::string> split_cmd = splitter(cmd);
    size_t found = cmd.find_first_not_of(" \t\v");
    if(found != std::string::npos)
        cmd = cmd.substr(found);
    if(split_cmd.size() && (split_cmd[0] == "PASS") ||( split_cmd[0] == "pass"))
        pass_cmd(split_cmd, fd);
    else if(split_cmd.size() && (split_cmd[0] == "NICK") || (split_cmd[0] == "nick"))
        nick_cmd(split_cmd, fd);
    else if(split_cmd.size() && (split_cmd[0] == "USER") || (split_cmd[0] == "user"))
        user_cmd(split_cmd, fd);
    else if(split_cmd.size() && (split_cmd[0] == "JOIN") || (split_cmd[0] == "join"))
        join_cmd(split_cmd, fd);
    else if(notregistered(fd))
    {
        std::cout << "AYESHAS PART" << std::endl;
    }
    else if (!notregistered(fd))
        err_unknowncmd(fd);
}