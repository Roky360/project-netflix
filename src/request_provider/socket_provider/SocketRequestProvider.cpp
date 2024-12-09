#include "SocketRequestProvider.h"
#include <sys/socket.h>   // For socket(), AF_INET, SOCK_STREAM
#include <netinet/in.h>   // For sockaddr_in
#include <unistd.h>       // For close()
#include <cstring>        // For memset()
#include <arpa/inet.h>    // For INADDR_ANY
#include <sstream>        // For stringstream
#include <iostream>       // For std::cerr


Request* SocketRequestProvider::nextRequest() {
    // get the server port from the state manager
    const int serverPort = StateManager::getInstance()->getServerPort();

    // create the socket and check if it worked
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return nullptr;
    }

    // cretae struct that holds the server IP and port. this will get the message. initializes the structure to zero.
    struct sockaddr_in sin;
    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(serverPort);

    // bind the socket and check for error
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        close(sock);
        return nullptr;
    }

    // listens for incoming connections. max 5 connections. check for errors
    if (listen(sock, 5) < 0) {
        perror("error listening to a socket");
        close(sock);
        return nullptr;
    }

    // struct to hold the client's IP and port
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin); // enter the size of the client_sin

    // accept the connection
    int client_sock = accept(sock, (struct sockaddr *) &client_sin,  &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
        close(sock);
        return nullptr;
    }

    // holds the message from the client
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(client_sock, buffer, expected_data_len, 0);
    if (read_bytes < 0) {
        perror("Error receiving data");
        close(client_sock);
        close(sock);
        return nullptr;
    }

    // Parse received data
    string input(buffer); // hold the input from the user
    stringstream ss(input); // Use a string stream to parse the input string

    string reqName; // holds the request name
    vector<std::string> args;

    // get the first word as the request name
    ss >> reqName;

    // read the rest of the line and enter them to args
    string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }

    // create a ClientContext with the client socket
    ClientContext* clientContext = new ClientContext(client_sock);

    // close the server socket (if no further connections are required)
    close(sock);

    // return the request using from name function
    return Request::fromName(reqName, args, clientContext);
}