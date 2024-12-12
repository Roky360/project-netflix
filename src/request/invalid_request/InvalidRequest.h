#ifndef PROJECT_NETFLIX_INVALIDREQUEST_H
#define PROJECT_NETFLIX_INVALIDREQUEST_H

#include "../Request.h"

/**
 * Represents a request that doesn't exist.
 */
class InvalidRequest : public Request {
public:
    InvalidRequest(const vector<string> &args, ClientContext* cl);

    string getHelpMsg() override;

    /**
     * return new invalid request response
     * @return
     */
    Response *execute() override;
};


#endif
