#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>  // Store string like password, name
#include <set>     // Store unique elements like FDs

/*******************************************************
 * Channel.hpp
 *
 * Description:
 *  This class represents a single IRC channel in the
 *  ft_irc server. It is responsible for maintaining
 *  channel-specific data such as:
 *    - Channel name and topic
 *    - Channel modes (invite-only, password, etc.)
 *    - List of members and operators
 *    - Invited users for invite-only mode
 *    - Permissions and user limits
 *
 *  The Channel class provides methods to:
 *    - Add and remove members
 *    - Assign or remove operator privileges
 *    - Set and enforce channel modes like +i, +k, +t, +l, +o
 *    - Manage topic and access control
 *
 *  This class will be used by the command parser to
 *  execute commands such as JOIN, PART, TOPIC, MODE,
 *  KICK, and INVITE.
 *
 *******************************************************/

class Channel {
private:
    std::string _name;        // Name of the channel #room
    std::string _topic;       // Topic/description of the channel
    std::string _password;    // Password for +k mode
    int _userLimit;           // User limit for +l mode

    bool _inviteOnly;         // Mode +i
    bool _topicRestricted;    // Mode +t
    bool _hasPassword;
    bool _hasUserLimit;

    // Containers
    std::set<int> _members;     // All current clients in the channel
    std::set<int> _operators;   // Clients with operator status
    std::set<int> _invited;     // Invited clients (for +i)

public:
    // Constructor
    Channel(const std::string& name);

    // Member management
    void addMember(int fd);
    void removeMember(int fd);
    bool hasMember(int fd) const;

    // Operator management
    void addOperator(int fd);
    void removeOperator(int fd);
    bool isOperator(int fd) const;

    // Invite management
    void addInvited(int fd);
    bool isInvited(int fd) const;
    void clearInvited();              // helper

    // Topic handling
    void setTopic(const std::string& topic);
    const std::string& getTopic() const;

    // Mode setters
    void setInviteOnly(bool value);
    void setTopicRestricted(bool value);
    void setPassword(const std::string& pass);
    void removePassword();
    void setUserLimit(int limit);
    void removeUserLimit();

    // Mode accessors
    bool isInviteOnly() const;
    bool isTopicRestricted() const;
    bool hasPassword() const;
    bool hasUserLimit() const;
    int getUserLimit() const;
    bool isFull() const;              //helper

    // Info access
    const std::string& getName() const;
    int getUserCount() const;
};

#endif // CHANNEL_HPP