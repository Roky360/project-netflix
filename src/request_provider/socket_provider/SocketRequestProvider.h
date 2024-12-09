#ifndef PROJECT_NETFLIX_SOCKETREQUESTPROVIDER_H
#define PROJECT_NETFLIX_SOCKETREQUESTPROVIDER_H

#include "../RequestProvider.h"
#include "../../request/Request.h"
#include "../../app/StateManager.h"

using namespace app;

/**
 * Provides requests from the socket.
 */
class SocketRequestProvider : public RequestProvider {
public:
    /**
     * return from the socket the wanted request with the arguments
     * @return request
     */
    Request *nextRequest() override;
};


#endif
