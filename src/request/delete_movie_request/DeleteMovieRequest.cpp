#include "DeleteMovieRequest.h"
#include "../../services/MoviesService.h"
#include <string>

DeleteMovieRequest::DeleteMovieRequest(const vector<std::string> &args, ClientContext *cl) : Request(args, cl){}

DeleteMovieRequest::DeleteMovieRequest() : Request() {}

string DeleteMovieRequest::getHelpMsg() {
    return "DELETE, arguments: [userid] [movieid1] [movieid2] ...";
}

Response* DeleteMovieRequest::execute() {
    // get the move service instance
    MoviesService *service = MoviesService::getInstance();

    // get the database instance
    Database* db = StateManager::getInstance()->getDb();

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
    if (!db->userExist(userId)) {
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
        if (!db->userHasMovie(userId, movieId)) {
            return new Response(NOT_FOUND_404, this->context);
        }
    }

    // for each movie send to delete function in the service
    for (auto movieId : movies) {
        service->deleteMovieFromUser(userId, movieId);
    }

    return new Response(OK_200, this->context);
}