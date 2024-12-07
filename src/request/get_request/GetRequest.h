#ifndef PROJECT_NETFLIX_GETREQUEST_H
#define PROJECT_NETFLIX_GETREQUEST_H

#include "../Request.h"
#include "../Response.h"

/**
 * Responsible for recommending additional movies to a user with a given movie.
 */
class GetRequest : public Request {
public:
    GetRequest();

    explicit GetRequest(const vector<string> &args, ClientContext* cl);

    string getHelpMsg() override;

    /**
     * execute the recommend function
     * @return response with the recommended movies
     */
    Response *execute() override;
};


#endif //PROJECT_NETFLIX_GETREQUEST_H
