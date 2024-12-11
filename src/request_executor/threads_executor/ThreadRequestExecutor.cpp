#include "ThreadRequestExecutor.h"

void ThreadRequestExecutor::execute(Request *request) {
    thread t1(&Request::execute, request);
    t1.join();
}
