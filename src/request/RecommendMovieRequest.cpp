#include "RecommendMovieRequest.h"
#include "../services/MoviesService.h"
#include "../database/Database.h"
#include <string>

RecommendMovieRequest::RecommendMovieRequest(const vector<string> &args) : Request(args) {}

RecommendMovieRequest::RecommendMovieRequest() :Request() {}

Response *RecommendMovieRequest::execute() {
    // get the movie service instance
    MoviesService *service = MoviesService::getInstance();

    if (args.size() > 2) {
        return new Response(INVALID_ARG, "To much arguments entered.");
    } else if (args.size() < 2) {
        return new Response(INVALID_ARG, "Did not entered enough arguments.");
    }

    // get the user id and the movie id and change it to integer
    int userId, movieId;
    try {
        userId = stoi(args[0]);
        movieId = stoi(args[1]);
    } catch (...) {
        return new Response(INVALID_ARG, "User ID and Movie ID must be numbers.");
    }

    // get the data base to check if the user exist
    Database* db = StateManager::getInstance()->getDb();

    // get the users ID
    vector<int> usersId = db->getAllUserIds();

    // if the user is not exist
    if(find(usersId.begin(), usersId.end(), userId) == usersId.end()) {
        return new Response(INVALID_ARG, "The user doesnt exist.");
    }

    // call recommend movies from the service and get the movies
    vector<int> recommended = service->recommendMovies(userId, movieId);

    // enter the recommended movies to string
    string payload;
    for (int i = 0; i < recommended.size(); ++i) {
        // try to convert the integers to string and if not return error
        try {
            payload += to_string(recommended[i]) + " ";
        } catch (...) {
            return new Response(ERROR);
        }
    }

    // return new response with the movies
    return new Response(OK, "", payload);
}
