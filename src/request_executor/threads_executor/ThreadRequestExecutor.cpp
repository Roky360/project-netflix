#include "ThreadRequestExecutor.h"

ThreadRequestExecutor::ThreadRequestExecutor(ResponseSender *responseSender) {
    rSender = responseSender;
}

void ThreadRequestExecutor::execute(Request *request) {
    thread t1(std::bind(&ThreadRequestExecutor::moveToSender, this, request));
    t1.join();
}

void ThreadRequestExecutor::moveToSender(Request *request) {
    Response *response = request->execute();
    rSender->sendResponse(response);
}
