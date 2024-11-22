#ifndef PROJECT_NETFLIX_ADDMOVIEREQUEST_H
#define PROJECT_NETFLIX_ADDMOVIEREQUEST_H

#include "Request.h"
#include "Response.h"


class AddMovieRequest: public Request {

    public:
        /**
         * add movies to the user, in the database
         * @return response
         */
        Response* execute();
        /**
         * constructor.
         */
        AddMovieRequest() = default;
};


#endif
