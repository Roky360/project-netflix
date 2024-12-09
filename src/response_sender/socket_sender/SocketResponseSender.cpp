#include "SocketResponseSender.h"

#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void SocketResponseSender::sendResponse(Response *response) {
    // send back the data to the client
    int sent_bytes = send(response->context->getField(), buffer, read_bytes, 0);

    if (sent_bytes < 0) {
        perror("error sending to client");
    }

    close(client_sock); // close the connection with the client
    close(sock); // close the server's socket (no longer accepts clients)
}
