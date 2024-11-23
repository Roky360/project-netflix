//
// Created by avi on 11/22/2024.
//

#ifndef PROJECT_NETFLIX_MOVIESSERVICE_H
#define PROJECT_NETFLIX_MOVIESSERVICE_H
#include "../database/Database.h"
#include "../StateManager.h"
#include <string>
#include <vector>
using namespace db;
using namespace std;

class MoviesService {
public:
// Delete copy constructor and assignment operator to ensure a single instance
    MoviesService(const MoviesService &) = delete;
    MoviesService &operator=(const MoviesService &) = delete;

    /**
     * Returns the single MovieService instance, makes sure there is only one instance existing
     * at all times, Static method to provide global access
     * @return StateManager
     */
    static MoviesService *getInstance();

    /**
     * Adds a movie to a user's watched list
     * @param userID The user
     * @param movieID The movie
     */
    void addMovieToUser(int userID, int movieID);

    /**
     * The original movie-recommendation algorithm of Nakniki-Netflix!
     * Recommends movies to users based on their shared watched movies with other like minded users
     * @param userID String, the user getting the recommend
     * @param movieID String, movie, the movie the user wishes to inspect
     * @return  Vector<string>, returns a string of up to 10 recommended movies in order
     */
    vector<int> recommendMovies(int userID, int movieID);

    /**
     * Returns all the other users that watched the same movie as the given movie, and are not the user
     * @param userID int, The userID we want to compare them to
     * @param movieID int, The movieID we check if they watched
     * @return vector<int>
     */
    vector<int> getComparableUsers(int userID, int movieID);

    /**
     * Ranks the users's likeness to userID, they get a point for each common movie with the user
     * @param userID int, The user they will be compared to
     * @param comparedUsers, vector<int>, the rest of the users which we wish to rank
     * @return vector<int>, a vector of all the grades of each user (not including userID
     */
    vector<int> rankComparableUsers(int userID, vector<int> comparedUsers);

private:
    static MoviesService *instance;
    Database *db;

    MoviesService() = default;
};


#endif //PROJECT_NETFLIX_MOVIESSERVICE_H
