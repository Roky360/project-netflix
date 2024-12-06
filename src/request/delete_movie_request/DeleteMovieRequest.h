#ifndef PROJECT_NETFLIX_DELETEMOVIEREQUEST_H
#define PROJECT_NETFLIX_DELETEMOVIEREQUEST_H

#include "../Request.h"
#include "../Response.h"

class DeleteMovieRequest : public Request{
public:
    DeleteMovieRequest();

    explicit DeleteMovieRequest(const vector<string> &args, ClientContext* cl);

    string getHelpMsg() override;

    /**
     * add movies to the user, in the database
     * @return response
     */
    Response *execute() override;
};


#endif
