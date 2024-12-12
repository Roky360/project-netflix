#include "ThreadRequestExecutor.h"

#include <iostream>

ThreadRequestExecutor::ThreadRequestExecutor(ResponseSender *responseSender) : RequestExecutor() {
    rSender = responseSender;
}

void ThreadRequestExecutor::execute(Request *request) {
    thread t1(std::bind(&ThreadRequestExecutor::moveToSender, this, request));
    t1.join();
}

void ThreadRequestExecutor::moveToSender(Request *request) {
    Response *response = request->execute();
    rSender->sendResponse(response);
    cout << "sent to " << request->context->getClientSocket() << endl; // TODO: remove
}
