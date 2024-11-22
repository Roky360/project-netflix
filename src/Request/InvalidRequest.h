#ifndef PROJECT_NETFLIX_INVALIDREQUEST_H
#define PROJECT_NETFLIX_INVALIDREQUEST_H
#include "Request.h"

class InvalidRequest: public Request {

    public:
        /**
         * return new invalid request response
         * @return
         */
        Response* execute() override;
        /**
         * default constructor
         */
        InvalidRequest() = default;
};


#endif
