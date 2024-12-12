#include "ThreadRequestExecutor.h"
#include "../../app/StateManager.h"
#include <iostream>

ThreadRequestExecutor::ThreadRequestExecutor(ResponseSender *responseSender, RequestProvider* rp) : RequestExecutor() {
    rSender = responseSender;
    rProvider = rp;
}

void ThreadRequestExecutor::execute(ClientContext* clientContext) {
    thread t1(std::bind(&ThreadRequestExecutor::moveToSender, this, clientContext));
    t1.join();
}

void ThreadRequestExecutor::moveToSender(ClientContext* cl) {
    while (true) {
        Request* request = rProvider->nextRequest(cl);

        if (request == nullptr) {
            cout << "ended" << endl; // TODO: remove
            break;
        }

        Response *response = request->execute();
        rSender->sendResponse(response);
        cout << "sent to " << request->context->getClientSocket() << endl; // TODO: remove
    }
}
