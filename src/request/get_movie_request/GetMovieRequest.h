#ifndef PROJECT_NETFLIX_GETMOVIEREQUEST_H
#define PROJECT_NETFLIX_GETMOVIEREQUEST_H

#include "../Request.h"
#include "../Response.h"

/**
 * Responsible for recommending additional movies to a user with a given movie.
 */
class GetMovieRequest : public Request {
public:
    GetMovieRequest();

    explicit GetMovieRequest(const vector<string> &args, ClientContext* cl);

    string getHelpMsg() override;

    /**
     * execute the recommend function
     * @return response with the recommended movies
     */
    Response *execute() override;
};


#endif //PROJECT_NETFLIX_GETMOVIEREQUEST_H
