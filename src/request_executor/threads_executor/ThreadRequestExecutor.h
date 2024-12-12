#ifndef PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
#define PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
#include "../RequestExecutor.h"
#include "../../response_sender/ResponseSender.h"
#include "../../app/StateManager.h"
#include <thread>
#include <functional>

using namespace app;
using namespace std;

class ThreadRequestExecutor : public RequestExecutor{
public:
    /**
     * Executes a request, and locks the database while executing
     * @param request Request
     */
    void execute(Request *request);
private:
    void moveToSender(Request *request);
};


#endif //PROJECT_NETFLIX_THREADREQUESTEXECUTOR_H
