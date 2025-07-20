#include "Channel.hpp"
#include <iostream>

// 1. Constructor: initialize the channel with default settings
Channel::Channel(const std::string& name)
    : _name(name),
      _topic(""),
      _password(""),
      _userLimit(0),
      _inviteOnly(false),
      _topicRestricted(false),
      _hasPassword(false),
      _hasUserLimit(false)
{
    std::cout << "[Channel created] Name: " << _name << std::endl;
}

// 2. Add a user to the member list
void Channel::addMember(int fd) {
    _members.insert(fd);
    _invited.erase(fd);  //if invited-> remove from invite list
    std::cout << "[Channel] User FD " << fd << " added to " << _name << std::endl;
}

// 3. Remove a user from the member and operator list
void Channel::removeMember(int fd) {
    _members.erase(fd);
    _operators.erase(fd); // Remove operator rights

    std::cout << "[Channel] User FD " << fd << " removed from " << _name << std::endl;
}

// 4. Check if a user is in the channel
bool Channel::hasMember(int fd) const {
    return _members.find(fd) != _members.end();
}

// 5. Get the total number of users in the channel
int Channel::getUserCount() const {
    return _members.size();
}