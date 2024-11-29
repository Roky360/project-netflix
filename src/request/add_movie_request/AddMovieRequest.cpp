#include "AddMovieRequest.h"
#include "../../services/MoviesService.h"
#include <string>

AddMovieRequest::AddMovieRequest(const vector<string> &args) : Request(args) {
}

AddMovieRequest::AddMovieRequest() : Request() {
}

Response *AddMovieRequest::execute() {
    // get the move service instance
    MoviesService *service = MoviesService::getInstance();

    // if the user didnt entered enough arguments.
    if (args.size() <= 1) {
        return new Response(INVALID_ARG, "Not enough arguments.");
    }

    // get the user id from the arguments
    int userId;
    try {
        userId = stoi(args[0]);
    } catch (...) {
        return new Response(INVALID_ARG, "User ID must be numbers.");
    }

    // call add movie service for each movie
    for (int i = 1; i < args.size(); ++i) {
        // try to change the movie id type to int
        try {
            service->addMovieToUser(userId, stoi(args[i]));
        } catch (...) {
            return new Response(INVALID_ARG, "Movie ID must be numbers.");
        }
    }

    // return ok response
    return new Response();
}
