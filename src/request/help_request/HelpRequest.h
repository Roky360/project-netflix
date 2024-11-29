#ifndef PROJECT_NETFLIX_HELPREQUEST_H
#define PROJECT_NETFLIX_HELPREQUEST_H

#include "../Request.h"

/**
 * Provides an explanation about all the supported commands.
 */
class HelpRequest : public Request {
public:
    HelpRequest();

    explicit HelpRequest(const vector<string> &args);

    string getHelpMsg() override;

    /**
     * execute the help request - print the menu
     * @return response
     */
    Response *execute() override;
};


#endif
