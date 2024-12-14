#include "ClientContext.h"

ClientContext::ClientContext(const int cs) : clientSocket(cs) {}

int ClientContext::getClientSocket() const {
    return this->clientSocket;
}