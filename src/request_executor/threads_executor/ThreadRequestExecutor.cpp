#include "ThreadRequestExecutor.h"


void ThreadRequestExecutor::execute(Request *request) {
    thread t1(std::bind(&ThreadRequestExecutor::moveToSender, this, request));
    t1.join();
}

void ThreadRequestExecutor::moveToSender(Request *request) {
    auto sm = StateManager::getInstance();
    auto rs = sm->getResponseSender();
    Response *response = request->execute();
    rs->sendResponse(response);
}
