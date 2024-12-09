#include "ClientContext.h"
#include <stdexcept>

ClientContext::ClientContext(int cs) : clientSocket(cs) {}

int ClientContext::getClientSocket() {
    return this->clientSocket;
}