#include "ThreadRequestExecutor.h"

void execute(Request *request) {
    thread t1(execute, request);
    t1.join();
}

