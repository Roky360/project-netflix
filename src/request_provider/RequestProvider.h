#ifndef PROJECT_NETFLIX_REQUESTPROVIDER_H
#define PROJECT_NETFLIX_REQUESTPROVIDER_H

#include "../request/Request.h"

/**
 * Provides requests to the server.
 */
class RequestProvider {
public:
    virtual ~RequestProvider() = default;

    /**
     * return the request from the user from the provider device
     * @return request, or nullptr if error has occurred.
     */
    virtual Request *nextRequest(ClientContext* cl) = 0;

    /**
     * listen and accept the users. return the user context
     * @return user context, or nullptr in case of an error.
     */
    virtual ClientContext *acceptClient() = 0;
};

#endif
