#ifndef PROJECT_NETFLIX_REQUESTPROVIDER_H
#define PROJECT_NETFLIX_REQUESTPROVIDER_H

#include "../Request/Request.h"

class RequestProvider {
    public:
        virtual Request* nextRequest() = 0;
};

#endif