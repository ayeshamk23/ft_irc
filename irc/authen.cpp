#include "replies.hpp"
void server::pass_cmd(std::string cmd, int fd)
{
    Client *cli = GetClient(fd);
    cmd = cmd.substr(4);
    size_t pos = cmd.find_first_not_of(" \t\v");
    if(pos<cmd.size())
    {
        cmd = cmd.substr(pos);
        if(cmd[0] == ':')
            cmd.erase(cmd.begin());
    }
    if(pos = std::string::npos ||cmd.empty())
    {
        responsesender(ERR_NOTENOUGHPARAMS(std::string("*")), fd);
    }
    else if(!cli->getregitered())
    {
        std::string pass = cmd;
        if(pass_cmd == pass)
            cli->setregistered(true);
        else
        responsesender(ERR_PASSWDMISMATCH(std::string ("*")), fd);
    }
    else
        responsesender(ERR_ALREADYREGISTRED(cli->getnickname()), fd);
}