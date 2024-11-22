#ifndef PROJECT_NETFLIX_HELPREQUEST_H
#define PROJECT_NETFLIX_HELPREQUEST_H
#include "Request.h"
#include <string>
#include <iostream>

class HelpRequest: public Request {

    public:
        Response* execute() override;
        HelpRequest() = default;

};


#endif
