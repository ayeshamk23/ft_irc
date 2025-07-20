#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client {
public:
    Client() : authenticated(false) {}

    void setNickname(const std::string& nick) { nickname = nick; }
    std::string getNickname() const { return nickname; }

    void setUsername(const std::string& user) { username = user; }
    std::string getUsername() const { return username; }

    void authenticate() { authenticated = true; }
    bool isAuthenticated() const { return authenticated; }

private:
    std::string nickname;
    std::string username;
    bool authenticated;
};

#endif
