#include "SocketRequestProvider.h"
#include <sys/socket.h>   // For socket(), AF_INET, SOCK_STREAM
#include <netinet/in.h>   // For sockaddr_in
#include <unistd.h>       // For close()
#include <cstring>        // For memset()
#include <arpa/inet.h>    // For INADDR_ANY
#include <sstream>        // For stringstream
#include <iostream>       // For std::cerr
#include <utility>

// Constructor implementation
SocketRequestProvider::SocketRequestProvider(const int port, string ip, const int backlog)
    : serverPort(port), serverIP(std::move(ip)), backlogAmount(backlog) {
    // create the socket and check if it worked
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        return;
    }
    this->serverSock = sock;

    // create struct that holds the server IP and port. this will get the message. initializes the structure to zero.
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(this->serverPort);

    // bind the socket and check for error
    if (bind(this->serverSock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        close(this->serverSock);
        return;
    }

    // listens for incoming connections. max 5 connections. check for errors
    if (listen(sock, this->backlogAmount) < 0) {
        perror("error listening to a socket");
        close(this->serverSock);
        return;
    }
    cout << "sock bind and listen to " << this->serverIP << " port " << this->serverPort << endl; // TODO: remove
}

SocketRequestProvider::~SocketRequestProvider() {
    close(this->serverSock);
}

Request *SocketRequestProvider::nextRequest() {
    // struct to hold the client's IP and port
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin); // enter the size of the client_sin

    // accept the connection
    int client_sock = accept(this->serverSock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        perror("error accepting client");
        close(this->serverSock);
        return nullptr;
    }
    cout << "client accepted" << endl; // TODO: remove

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
    ClientContext *clientContext = new ClientContext(client_sock);

    // return the request using from name function
    return Request::fromName(reqName, args, clientContext);
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

// stringstream SocketRequestProvider::readSocketToStream(int socket) {
//     stringstream ss;
//     char buffer[1024]; // temporary for incoming chunks
//     int bytesReceived;
//
//     // read data from the socket in chunks
//     while ((bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
//         cout << "reveiving..." << endl; // TODO: remove
//         buffer[bytesReceived] = '\0';
//         ss.write(buffer, bytesReceived);
//         cout << "reveiving 2..." << endl; // TODO: remove
//     }
//
//     // if there was problem
//     if (bytesReceived < 0) {
//         cout << "reveiving 2.2..." << endl; // TODO: remove
//         perror("Error receiving data");
//         ss.str(""); // reset the stream content
//         ss.clear();
//     }
//     cout << "reveiving 3..." << endl; // TODO: remove
//
//     return ss;
// }

stringstream SocketRequestProvider::readSocketToStream(int socket) {
    std::stringstream ss;
    char buffer[1024]; // temporary for incoming chunks

    // Read data from the socket in chunks
    bool finishedReceiving = false;
    while (!finishedReceiving) {
        int bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived < 0) {
            perror("recv failed");
            return {};
        }

        ss.write(buffer, bytesReceived);

        // Optional: check if you have received a complete message
        if (strchr(buffer, '\n')) {
            finishedReceiving = true;
        }

        // Reset buffer for next chunk
        // memset(buffer, 0, sizeof(buffer));
    }

    return ss;
}
