#ifndef PROJECT_NETFLIX_CLIREQUESTPROVIDER_H
#define PROJECT_NETFLIX_CLIREQUESTPROVIDER_H

#include "../RequestProvider.h"
#include "../../request/Request.h"


/**
 * Provides requests from the CLI.
 */
class CliRequestProvider : public RequestProvider {
public:
    /**
     * return from the user, in console, the wanted request
     * @return request
     */
    Request *nextRequest() override;
};


#endif
