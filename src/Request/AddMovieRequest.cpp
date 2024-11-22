#include "AddMovieRequest.h"
#include <string>

Response* AddMovieRequest::execute() {
    // get the move service instance
    MovieService* service = MovieService::getInstance();

    // get the user id
    string userId = args[0];

    // call add movie service for each movie
    for (int i = 1; i < args.size(); ++i) {
        service.addMovieToUser(userId, args[i]);
    }

    // return ok response
    return new Response();
}