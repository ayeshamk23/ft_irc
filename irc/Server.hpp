#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <stdlib.h>

class Server {
private:
    int _port;
    std::string _password;
    int _serverSocket;

public:
    Server(int port, const std::string &password);
    ~Server();

    void start();
};

#endif
