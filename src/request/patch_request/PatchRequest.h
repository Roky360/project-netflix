#ifndef PROJECT_NETFLIX_PATCHREQUEST_H
#define PROJECT_NETFLIX_PATCHREQUEST_H

#include "../Request.h"
#include "../Response.h"

/**
 * Responsible for marking movies as watched to already exist users.
 */
class PatchRequest : public Request {
public:
    PatchRequest();

    explicit PatchRequest(const vector<string> &args, ClientContext* cl);

    string getHelpMsg() override;

    /**
     * add movies to the user, in the database. only to exist user
     * @return response
     */
    Response *execute() override;
};


#endif
