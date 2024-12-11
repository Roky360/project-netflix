#ifndef PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
#define PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
#include "../RequestExecutor.h"
#include <thread>

class ThreadRequestExecutor : public RequestExecutor{
public:
    /**
     * Executes a request, and locks the database while executing
     * @param request Request
     */
    void execute(Request *request);
};


#endif //PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
