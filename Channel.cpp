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

void Channel::removeMember(int fd, const std::string& nickname) {
    _members.erase(fd);
    _operators.erase(nickname); // correct type used here
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


void Channel::addOperator(const std::string& nickname) {
    _operators[nickname] = true;
}

void Channel::removeOperator(const std::string& nickname) {
    _operators.erase(nickname);
}

bool Channel::isOperator(const std::string& nickname) const {
    std::map<std::string, bool>::const_iterator it = _operators.find(nickname);
    if (it != _operators.end())
        return it->second;
    return false;
}

// Invite handling
void Channel::addInvited(int fd) {
    _invited.insert(fd);
}

bool Channel::isInvited(int fd) const {
    return _invited.find(fd) != _invited.end();
}

// Channel mode setters
void Channel::setInviteOnly(bool value) {
    _inviteOnly = value;
}

void Channel::setTopicRestricted(bool value) {
    _topicRestricted = value;
}

void Channel::setPassword(const std::string& pass) {
    _password = pass;
    _hasPassword = true;
}

void Channel::removePassword() {
    _password.clear();
    _hasPassword = false;
}

void Channel::setUserLimit(int limit) {
    _userLimit = limit;
    _hasUserLimit = true;
}

void Channel::removeUserLimit() {
    _userLimit = 0;
    _hasUserLimit = false;
}


bool Channel::isInviteOnly() const {
    return _inviteOnly;
}

bool Channel::isTopicRestricted() const {
    return _topicRestricted;
}

bool Channel::hasPassword() const {
    return _hasPassword;
}

bool Channel::hasUserLimit() const {
    return _hasUserLimit;
}


int Channel::getUserLimit() const {
    return _userLimit;
}

bool Channel::isFull() const {
    return _hasUserLimit && (_members.size() >= static_cast<size_t>(_userLimit));
}