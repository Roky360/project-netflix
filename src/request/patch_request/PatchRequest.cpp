#include "PatchRequest.h"
#include "../../services/MoviesService.h"
#include <string>

PatchRequest::PatchRequest(const vector<std::string> &args, ClientContext *cl) : Request(args, cl) {}

PatchRequest::PatchRequest() : Request() {}

string PatchRequest::getHelpMsg() {
    return "PATCH, arguments: [userid] [movieid1] [movieid2] ...";
}

Response* PatchRequest::execute() {
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

    // if the user not exist - return bad request
    if (!db->userExists(userId)) {
        return new Response(NOT_FOUND_404, this->context);
    }

    // enter the movies id to the vector
    vector<int> movies;
    for (int i = 1; i < args.size(); ++i) {
        // try to transfer to int and then push it
        try {
            auto movieId = stoi(args[i]);
            movies.push_back(movieId);
        } catch (...) {
            return new Response(BAD_REQUEST_400, this->context);
        }
    }

    // add the movie to the user
    for (auto movieID : movies) {
        service->addMovieToUser(userId, movieID);
    }

    // return ok response
    return new Response(OK_200, this->context);

}