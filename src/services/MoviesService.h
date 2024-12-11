//
// Created by avi on 11/22/2024.
//

#ifndef PROJECT_NETFLIX_MOVIESSERVICE_H
#define PROJECT_NETFLIX_MOVIESSERVICE_H
#include "../database/Database.h"
#include "../app/StateManager.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace db;
using namespace std;
using namespace app;

class MoviesService {
public:
    const int MOVIE_RECOMMENDATION_COUNT = 10;

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
     *  The original movie-recommendation algorithm of Nakniki-Netflix!
     * Recommends movies to users based on their shared watched movies with other like minded users
     * @param userID String, the user getting the recommend
     * @param movieID String, movie, the movie the user wishes to inspect
     * @return  Vector<string>, returns a string of up to 10 recommended movies in order
     */
    vector<int> recommendMovies(int userID, int movieID);

    /**
     * Deletes a movie from a user's watched list
     * @param userId int, the user's id
     * @param movieId int, the movie's id
     */
    void deleteMovieFromUser(int userId, int movieId);

    /**
     * Checks whether a user has seen a movie
     * @param userID int, the user's ID
     * @param movieID int, the movie's ID
     * @return
     */
    bool userHasMovie(int userID, int movieID);

    /**
     * Checks whether a user is registered to our database
     * @param userID int, the user we wish to check
     * @return
     */
    bool userExists (int userID);


private:
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
    vector<int> rankComparableUsers(int userID, vector<int> *comparedUsers);

    /**
     * Creates the final scores of each movie in a map
     * @param userID the original user we compare the rest to
     * @param movieID the movie the original user inquired about
     * @param users vector<int> The list of users compared
     * @param ranks vector<int> The recommendation values of each user
     * @return map<int, int>, the map containing each movie, and their recommendation score
     */
    map<int, int> mapComparableMovies(int userID, int movieID, vector<int> *users, vector<int> *ranks);

    static bool initialized;
    static MoviesService *instance;

    MoviesService() = default;
};


#endif //PROJECT_NETFLIX_MOVIESSERVICE_H
