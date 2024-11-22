#ifndef PROJECT_NETFLIX_INVALIDREQUEST_H
#define PROJECT_NETFLIX_INVALIDREQUEST_H
#include "Request.h"

class InvalidRequest: public Request {

    public:
        Response* execute() override;
        InvalidRequest() = default;
};


#endif
