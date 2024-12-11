#ifndef PROJECT_NETFLIX_REQUESTEXECUTOR_H
#define PROJECT_NETFLIX_REQUESTEXECUTOR_H

#include "../request/Request.h"
/**
 * Executes client requests
 */
class RequestExecutor {
public:
    /**
     * Executes each request according to their own execute method
     * @param request Request
     */
    virtual void execute(Request request);
};


#endif //PROJECT_NETFLIX_REQUESTEXECUTOR_H
