#ifndef PROJECT_NETFLIX_RECOMMANDMOVIEREQUEST_H
#define PROJECT_NETFLIX_RECOMMANDMOVIEREQUEST_H
#include "Request.h"
#include "Response.h"

class RecommandMovieRequest: public Request {

    public:
        /**
         * execute the recommend functio
         * @return response with the recommended movies
         */
        Response* execute();
        /**
         * default constructor
         */
        RecommandMovieRequest() = default;
};


#endif //PROJECT_NETFLIX_RECOMMANDMOVIEREQUEST_H
