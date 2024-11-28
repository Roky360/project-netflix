#ifndef PROJECT_NETFLIX_RECOMMENDMOVIEREQUEST_H
#define PROJECT_NETFLIX_RECOMMENDMOVIEREQUEST_H
#include "Request.h"
#include "Response.h"

class RecommendMovieRequest : public Request {
public:
    /**
     * execute the recommend functio
     * @return response with the recommended movies
     */
    Response *execute();

    RecommendMovieRequest();

    explicit RecommendMovieRequest(const vector<string> &args);
};


#endif //PROJECT_NETFLIX_RECOMMENDMOVIEREQUEST_H
