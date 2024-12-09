#include "SocketRequestProvider.h"
#include <sys/socket.h>   // For socket(), AF_INET, SOCK_STREAM
#include <netinet/in.h>   // For sockaddr_in
#include <unistd.h>       // For close()
#include <cstring>        // For memset()
#include <arpa/inet.h>    // For INADDR_ANY
#include <sstream>        // For stringstream
#include <iostream>       // For std::cerr

// Constructor implementation
SocketRequestProvider::SocketRequestProvider(int port, string ip, int backlog)
    : serverPort(port), serverIP(ip), backlogAmount(backlog) {}

stringstream SocketRequestProvider::readSocketToStream(int socket) {
    stringstream ss;
    char buffer[1024]; // temporary for incoming chunks
    int bytesReceived;

    // read data from the socket in chunks
    while ((bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[bytesReceived] = '\0';
        ss << buffer;
    }

    // if there was problem
    if (bytesReceived < 0) {
        perror("Error receiving data");
        ss.str("");  // reset the stream content
        ss.clear();
    }

    return ss;
}

vector<string> SocketRequestProvider::parseArguments(stringstream &ss) {
    vector<string> args; // holds the arguments

    // read the arguments of the line and enter them to args
    string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }

    return args;
}

Request* SocketRequestProvider::nextRequest() {
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
    sin.sin_addr.s_addr = this->serverIP;
    sin.sin_port = htons(this->serverPort);

    // bind the socket and check for error
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        close(sock);
        return nullptr;
    }

    // listens for incoming connections. max 5 connections. check for errors
    if (listen(sock, this->backlogAmount) < 0) {
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

    // get the client msg into the stream
    stringstream ss = this->readSocketToStream(client_sock);

    // if the stream is empty: handle the error
    if (ss.str().empty()) {
        close(client_sock);
        return nullptr;
    }

    // holds the request name
    string reqName;

    // get the first word as the request name
    ss >> reqName;

    // get the other arguments
    vector<string> args = this->parseArguments(ss);

    // create a ClientContext with the client socket
    ClientContext* clientContext = new ClientContext(client_sock);

    // close the server socket (if no further connections are required)
    close(sock);

    // return the request using from name function
    return Request::fromName(reqName, args, clientContext);
}