#include "SocketResponseSender.h"

#include <sys/socket.h>

void SocketResponseSender::sendResponse(Response *response) {
    auto clientSock = response->context->getClientSocket();
    auto resData = response->toRawData();
    send(clientSock, resData.c_str(), resData.length(), 0);
}
