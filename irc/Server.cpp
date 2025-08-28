#include "Server.hpp"  
// Includes the header file that declares the Server class

#include <iostream>     
// For printing messages to the terminal using std::cout

#include <sys/socket.h> 
// Provides socket(), bind(), listen(), etc. for network communication

#include <netinet/in.h> 
// Defines sockaddr_in and constants for internet protocols

#include <unistd.h>     
// Gives us access to close() function to close sockets

#include <fcntl.h>      
// For setting socket to non-blocking (used later, not here yet)

#include <cstring>      
// For using memset() to zero out memory

// Constructor for the Server class
Server::Server(int port, const std::string &password)
    : _port(port), _password(password) {} 
// It stores the given port and password in the server’s variables

// Destructor for the Server class
Server::~Server() {
    close(_serverSocket);  
    // When the server object is destroyed, close the socket (clean up)
}

void Server::start() {
    // STEP 1: Create a socket
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    // socket() returns a file descriptor (number) used to refer to the socket.
    // AF_INET → IPv4
    // SOCK_STREAM → TCP (stream-based, reliable)
    // 0 → use default protocol for TCP

    if (_serverSocket < 0) {
        throw std::runtime_error("Failed to create socket");
        // If socket creation failed, throw an error
    }

    // STEP 2: Set socket options
    int opt = 1;
    setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    // SO_REUSEADDR allows us to reuse the port immediately after restarting the server.
    // Without this, you might get "port already in use" errors

    // STEP 3: Prepare address info (where to bind the server)
    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    // Zero out the memory (very common in C/C++ for safety)

    serverAddr.sin_family = AF_INET; // Use IPv4
    serverAddr.sin_addr.s_addr = INADDR_ANY; 
    // INADDR_ANY = listen on any of the host’s IP addresses (localhost, etc.)
    
    serverAddr.sin_port = htons(_port); 
    // htons() converts your port number to "network byte order"
    // (network uses big-endian format)

    // STEP 4: Bind the socket to this IP/port
    if (bind(_serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Bind failed");
        // If bind fails, another program may be using this port
    }

    // STEP 5: Start listening for incoming connections
    if (listen(_serverSocket, 10) < 0) {
        throw std::runtime_error("Listen failed");
        // If listen fails, server can’t accept clients
    }

    std::cout << "Server started on port " << _port << std::endl;
    // Show message that server is up and running
}
