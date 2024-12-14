#include "DeleteRequest.h"
#include "../../services/MoviesService.h"
#include <string>

DeleteRequest::DeleteRequest(const vector<std::string> &args, ClientContext *cl) : Request(args, cl){}

DeleteRequest::DeleteRequest() : Request() {}

string DeleteRequest::getHelpMsg() {
    return "DELETE, arguments: [userid] [movieid1] [movieid2] ...";
}

Response* DeleteRequest::execute() {
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

    // check if the user exist
    if (!service->userExists(userId)) {
        return new Response(NOT_FOUND_404, this->context);
    }

    // enter the movies id to the vector
    vector<int> movies;
    for (int i = 1; i < args.size(); ++i) {
        // try to transfer to int and then push it
        try {
            int movieId = stoi(args[i]);
            movies.push_back(movieId);
        } catch (...) {
            return new Response(BAD_REQUEST_400, this->context);
        }
    }

    // check every movie if the user has them
    for (auto movieId : movies) {
        if (!service->userHasMovie(userId, movieId)) {
            return new Response(BAD_REQUEST_400, this->context);
        }
    }

    // for each movie send to delete function in the service
    for (auto movieId : movies) {
        service->deleteMovieFromUser(userId, movieId);
    }

    return new Response(NO_CONTENT_204, this->context);
}