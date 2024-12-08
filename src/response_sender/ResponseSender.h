#ifndef RESPONSESENDER_H
#define RESPONSESENDER_H

#include "../request/Response.h"

/**
* An interface that manages the sending of resonses to the client.
* Any implementation of this interface defines its own delivery method of the responses.
*/
class ResponseSender {
public:
    ResponseSender() = default;

    virtual ~ResponseSender() = default;

    /**
     * Sends a response back to the client.
     *
     * The ClientContext field of the `response` may be important, and it is assumed to be initialized appropriately.
     *
     * @param response Response object to send.
     */
    virtual void sendResponse(Response *response) = 0;
};

#endif //RESPONSESENDER_H
