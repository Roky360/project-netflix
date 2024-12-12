#include "ThreadRequestExecutor.h"
#include "../../app/StateManager.h"

ThreadRequestExecutor::ThreadRequestExecutor(ResponseSender *responseSender, RequestProvider *rp) : RequestExecutor() {
    rSender = responseSender;
    rProvider = rp;
}

void ThreadRequestExecutor::execute(ClientContext *clientContext) {
    // thread clientHandlerThr(std::bind(&ThreadRequestExecutor::handleClient, this, clientContext));
    auto t = new thread([this, clientContext] { handleClient(clientContext); });
    this->clientHandlers.push_back(t);
}

void ThreadRequestExecutor::handleClient(ClientContext *cl) {
    while (true) {
        Request *request = rProvider->nextRequest(cl);
        if (request == nullptr) {
            break;
        }
        Response *response = request->execute();
        rSender->sendResponse(response);
    }
}
