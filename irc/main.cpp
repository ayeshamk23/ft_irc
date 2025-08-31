 #include "Server.hpp"


int main(int argc, char **argv) 
{
    if (argc != 3) 
    {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return 1;
    }

    int port = atoi(argv[1]);
    std::string password = argv[2];

    try {
        Server server(port, password);
        server.start();
    } catch (const std::exception &e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }

    return 0;
}






// //this is inshas tester for command dispatcher and client authentication

// #include "CommandDispatcher.hpp"
// #include "Client.hpp"

// int main() {
//     Client client;
//     CommandDispatcher dispatcher;

//     dispatcher.dispatchCommand(client,
//         "PASS mypasword\r\n"
//         "NICK coolgirl\r\n"
//         "USER me 0 * :Cool Girl\r\n"
//     );

//     if (client.isAuthenticated()) {
//         std::cout << "Client is authenticated and ready!" << std::endl;
//         std::cout << "Nickname: " << client.getNickname() << std::endl;
//         std::cout << "Username: " << client.getUsername() << std::endl;
//     } else {
//         std::cout << "Client authentication failed." << std::endl;
//     }
// }

int main()
{

    parse(cmd, fd);
}
