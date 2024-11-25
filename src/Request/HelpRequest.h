#ifndef PROJECT_NETFLIX_HELPREQUEST_H
#define PROJECT_NETFLIX_HELPREQUEST_H
#include "Request.h"
#include <string>
#include <iostream>

class HelpRequest : public Request {
public:
    /**
     * execute the help request - print the menu
     * @return response
     */
    Response *execute() override;

    /**
     * default constructor.
     */
    HelpRequest() = delete;

    explicit HelpRequest(const vector<string>& args);
};


#endif
