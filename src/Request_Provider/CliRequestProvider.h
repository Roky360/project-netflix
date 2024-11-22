#ifndef PROJECT_NETFLIX_CLIREQUESTPROVIDER_H
#define PROJECT_NETFLIX_CLIREQUESTPROVIDER_H
#include "RequestProvider.h"
#include "../Request/Request.h"


class CliRequestProvider : public RequestProvider {

    public:
        /**
         * return from the user, in console, the wanted request
         * @return request
         */
        Request* nextRequest() override;
};


#endif
