#ifndef PROJECT_NETFLIX_REQUESTPROVIDER_H
#define PROJECT_NETFLIX_REQUESTPROVIDER_H

#include "../request/Request.h"

/**
 * Provides requests to the server.
 */
class RequestProvider {
public:
    /**
     * return the request from the user from the provider device
     * @return request
     */
    virtual Request *nextRequest() = 0;
};

#endif
