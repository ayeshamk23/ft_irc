
#include "Channel.hpp"
#include <iostream>

// int main() {
//     Channel myChannel("#general");

//     // Simulate user file descriptors
//     int user1 = 1;
//     int user2 = 2;

//     // Add members
//     myChannel.addMember(user1);
//     myChannel.addMember(user2);

//     // Check if members exist
//     std::cout << "User1 is member: " << myChannel.hasMember(user1) << std::endl;
//     std::cout << "User2 is member: " << myChannel.hasMember(user2) << std::endl;

//     // Show user count
//     std::cout << "User count: " << myChannel.getUserCount() << std::endl;

//     // Remove user1
//     myChannel.removeMember(user1);

//     // Check again
//     std::cout << "User1 is member after removal: " << myChannel.hasMember(user1) << std::endl;
//     std::cout << "User count after removal: " << myChannel.getUserCount() << std::endl;

//     return 0;
// }


#include "Channel.hpp"
#include <iostream>

int main() {
    Channel room("#general");

    room.addMember(1);
    room.addMember(2);
    room.addOperator("alice");

    std::cout << "User count: " << room.getUserCount() << "\n";
    std::cout << "Is alice operator? " << room.isOperator("alice") << "\n";

    room.setInviteOnly(true);
    room.addInvited(3);

    std::cout << "User 3 invited? " << room.isInvited(3) << "\n";

    room.setUserLimit(2);
    room.addMember(1);
    room.addMember(2);

    std::cout << "Is full? " << room.isFull() << "\n";
    std::cout << "Invite-only? " << room.isInviteOnly() << "\n";

    return 0;
}