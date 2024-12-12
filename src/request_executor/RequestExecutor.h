#ifndef PROJECT_NETFLIX_REQUESTEXECUTOR_H
#define PROJECT_NETFLIX_REQUESTEXECUTOR_H

#include "../request/Request.h"
/**
 * Executes client requests
 */
class RequestExecutor {
public:
    RequestExecutor() = default;

    virtual ~RequestExecutor() = default;

    /**
     * Executes each request according to their own execute method
     * @param request Request
     */
    virtual void execute(Request *request) = 0;
};


#endif //PROJECT_NETFLIX_REQUESTEXECUTOR_H
