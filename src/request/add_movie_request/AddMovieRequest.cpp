#include "AddMovieRequest.h"
#include "../../services/MoviesService.h"
#include <string>

AddMovieRequest::AddMovieRequest(const vector<string> &args, ClientContext* cl) : Request(args, cl) {}

AddMovieRequest::AddMovieRequest() : Request() {
}

string AddMovieRequest::getHelpMsg() {
    return "ADD, arguments: [userid] [movieid1] [movieid2] ...";
}

Response *AddMovieRequest::execute() {
    // get the move service instance
    MoviesService *service = MoviesService::getInstance();

    // if the user didnt entered enough arguments.
    if (args.size() <= 1) {
        return new Response(BAD_REQUEST_400, this->context);
    }

    // get the user id from the arguments
    int userId;
    try {
        userId = stoi(args[0]);
    } catch (...) {
        return new Response(BAD_REQUEST_400, this->context);
    }

    // call add movie service for each movie
    for (int i = 1; i < args.size(); ++i) {
        // try to change the movie id type to int
        try {
            service->addMovieToUser(userId, stoi(args[i]));
        } catch (...) {
            return new Response(BAD_REQUEST_400, this->context);
        }
    }

    // return ok response
    return new Response(OK_200, this->context);
}