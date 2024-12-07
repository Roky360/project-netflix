#ifndef PROJECT_NETFLIX_POSTREQUEST_H
#define PROJECT_NETFLIX_POSTREQUEST_H

#include "../Request.h"
#include "../Response.h"

/**
 * Responsible for create new users and marking movies as watched to them.
 */
class PostRequest : public Request {
public:
    PostRequest();

    explicit PostRequest(const vector<string> &args, ClientContext* cl);

    string getHelpMsg() override;

    /**
     * create user and add movies to the user, ONLY if the user not exist
     * @return response
     */
    Response *execute() override;

};


#endif