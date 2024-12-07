#include "PostRequest.h"
#include "../../services/MoviesService.h"
#include <string>

PostRequest::PostRequest() : Request() {}

PostRequest::PostRequest(const vector<std::string> &args, ClientContext *cl) : Request(args, cl) {}

string PostRequest::getHelpMsg() {
    return "POST, arguments: [userid] [movieid1] [movieid2] ...";
}

Response *PostRequest::execute() {
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

    // if the user alreadt exist - return bad request
    if (db->userExist(userId)) {
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

    return new Response(CREATED_201, this->context);
}