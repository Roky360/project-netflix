#include "RecommandMovieRequest.h"
#include <string>

Response* RecommandMovieRequest::execute() {
    // get the movie service instance
    MovieService* service = MovieService::getInstance();

    // the first string is the userid and second is movieid
    string userId = args[0];
    string movieId = args[1];

    // call recommend movies from the service and get the movies
    vector<string> recommended = service.recommendMovies(userId, movieId);

    // enter the movies to string
    string payload;
    for (int i = 0; i < recommended.size(); ++i) {
        payload += recommended[i] + " ";
    }

    // return new response with the movies
    return new Response(OK, "", payload);
}