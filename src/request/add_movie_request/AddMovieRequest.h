#ifndef PROJECT_NETFLIX_ADDMOVIEREQUEST_H
#define PROJECT_NETFLIX_ADDMOVIEREQUEST_H

#include "../Request.h"
#include "../Response.h"


/**
 * Responsible for marking movies as watched by users.
 */
class AddMovieRequest : public Request {
public:
    AddMovieRequest();

    explicit AddMovieRequest(const vector<string> &args);

    string getHelpMsg() override;

    /**
     * add movies to the user, in the database
     * @return response
     */
    Response *execute() override;
};


#endif
