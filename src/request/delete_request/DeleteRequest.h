#ifndef PROJECT_NETFLIX_DELETEREQUEST_H
#define PROJECT_NETFLIX_DELETEREQUEST_H

#include "../Request.h"
#include "../Response.h"

/**
 * Deletes a movie from a user - marks a movie as unwatched by a user.
 */
class DeleteRequest : public Request {
public:
    DeleteRequest();

    explicit DeleteRequest(const vector<string> &args, ClientContext *cl);

    string getHelpMsg() override;

    /**
     * delete movies from the user, in the database
     * @return response
     */
    Response *execute() override;
};


#endif
