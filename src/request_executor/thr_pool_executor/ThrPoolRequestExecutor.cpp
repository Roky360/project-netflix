#include "ThrPoolRequestExecutor.h"

ThrPoolRequestExecutor::ThrPoolRequestExecutor(RequestProvider *provider, ResponseSender *sender,
                                               ThreadPool *pool) : RequestExecutor() {
    this->provider = provider;
    this->sender = sender;
    this->pool = pool;
}

ThrPoolRequestExecutor::~ThrPoolRequestExecutor() {
    delete this->pool;
}

void ThrPoolRequestExecutor::execute(ClientContext *clientContext) {
    this->pool->enqueueTask([this, clientContext]() -> void {
        handleClient(clientContext);
    });
}

void ThrPoolRequestExecutor::handleClient(ClientContext *context) const {
    while (true) {
        Request *request = provider->nextRequest(context);
        // if client has closed the connection, exit and end the task
        if (request == nullptr) {
            break;
        }
        Response *response = request->execute();
        sender->sendResponse(response);
    }
}
