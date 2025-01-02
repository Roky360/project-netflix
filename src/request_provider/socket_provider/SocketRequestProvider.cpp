#include "SocketRequestProvider.h"
#include <sys/socket.h>   // For socket(), AF_INET, SOCK_STREAM
#include <netinet/in.h>   // For sockaddr_in
#include <unistd.h>       // For close()
#include <cstring>        // For memset()
#include <sstream>        // For stringstream
#include <iostream>       // For std::cerr
#include <utility>

// Constructor implementation
SocketRequestProvider::SocketRequestProvider(const int port, string ip, const int backlog)
    : serverPort(port), serverIP(std::move(ip)), backlogAmount(backlog) {
    // create the socket and check if it worked
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
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
        close(this->serverSock);
        return;
    }

    // listens for incoming connections. max 5 connections. check for errors
    if (listen(sock, this->backlogAmount) < 0) {
        close(this->serverSock);
        return;
    }
}

SocketRequestProvider::~SocketRequestProvider() {
    close(this->serverSock);
}

ClientContext *SocketRequestProvider::acceptClient() {
    // struct to hold the client's IP and port
    struct sockaddr_in client_sin;
    unsigned int addr_len = sizeof(client_sin); // enter the size of the client_sin

    // accept the connection
    int client_sock = accept(this->serverSock, (struct sockaddr *) &client_sin, &addr_len);
    if (client_sock < 0) {
        close(client_sock);
        return nullptr;
    }

    // return the ClientContext with the client socket
    return new ClientContext(client_sock);
}

Request *SocketRequestProvider::nextRequest(ClientContext *cl) {
    // get the client msg into the stream
    bool hasError;
    stringstream ss = this->readSocketToStream(cl->getClientSocket(), &hasError);

    // if the stream is empty: handle the error
    if (ss.str().empty()) {
        if (hasError) {
            return new InvalidRequest({}, cl);
        }
        close(cl->getClientSocket());
        return nullptr;
    }

    // holds the request name
    string reqName;

    // get the first word as the request name
    ss >> reqName;

    // get the other arguments
    vector<string> args = this->parseArguments(ss);

    // return the request using from name function
    return Request::fromName(reqName, args, cl);
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

stringstream SocketRequestProvider::readSocketToStream(int socket, bool *hasError) {
    stringstream ss;
    char buffer[1024]; // temporary for incoming chunks

    // Read data from the socket in chunks
    bool finishedReceiving = false;
    while (!finishedReceiving) {
        int bytesReceived = recv(socket, buffer, sizeof(buffer) - 1, 0);
        // error occurred while reading data
        if (bytesReceived < 0) {
            *hasError = true;
            return {};
        }
        // gracefully stopping
        if (bytesReceived == 0) {
            *hasError = false;
            return {};
        }

        ss.write(buffer, bytesReceived);

        // check if we got the whole message
        if (strchr(buffer, '\n')) {
            finishedReceiving = true;
        }
    }

    *hasError = false;
    return ss;
}
