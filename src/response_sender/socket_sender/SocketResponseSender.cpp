#include "SocketResponseSender.h"

#include <sys/socket.h>
#include <cstdio>
#include <unistd.h>

void SocketResponseSender::sendResponse(Response *response) {
    auto clientSock = response->context->getClientSocket();
    auto resData = response->toRawData();

    int bytesSent = send(clientSock, resData.c_str(), resData.length(), 0);

    if (bytesSent < 0) {
        perror("error sending to client");
    }

    close(clientSock);
}
