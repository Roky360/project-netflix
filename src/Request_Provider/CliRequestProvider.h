#ifndef PROJECT_NETFLIX_CLIREQUESTPROVIDER_H
#define PROJECT_NETFLIX_CLIREQUESTPROVIDER_H
#include "RequestProvider.h"
#include "../Request/Request.h"


class CliRequestProvider : public RequestProvider {

    public:
        Request* nextRequest() override;
};


#endif
