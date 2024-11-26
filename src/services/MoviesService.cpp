//
// Created by avi on 11/22/2024.
//

#include <iostream>
#include "MoviesService.h"

MoviesService *MoviesService::instance = nullptr;

MoviesService *MoviesService::getInstance() {
    if (instance == nullptr) {
        instance = new MoviesService();
    }
    return instance;
}


void MoviesService::addMovieToUser(int userID, int movieID) {
    Database *db = StateManager::getInstance()->getDb();
    db->addMovieToUser(userID, movieID);
}

vector<int> MoviesService::recommendMovies(int userID, int movieID) {

    vector<int> users = MoviesService::getComparableUsers(userID, movieID);
    vector<int> ranks = MoviesService::rankComparableUsers(userID, &users);
    map<int, int> movieMap = mapComparableMovies(userID, movieID, &users, &ranks);
    // Sets a vector to store all the possible movies we found (first) and their respective ranks (second)
    vector<pair<int, int>> pairs(movieMap.begin(), movieMap.end());
    //Lambda function to sort the vector
    std::sort(pairs.begin(), pairs.end(), [](const auto &a, const auto &b) {
        //Sorts them by the value of the "ranks" of the movies, their recommendation scores
        if (a.second == b.second) {
            return a.first < b.first;
        }
        return a.second > b.second;
    });

    //The vector we will return, including the top results for our recommendation
    vector<int> topTen;
    //The minimum between the number 10 and the number of fitting movies
    int mini = min(MOVIE_RECOMMENDATION_COUNT, (int) pairs.size());
    //Pushes the movies (stored in first) into the return vector
    for (int i = 0; i < mini; ++i) {
        topTen.push_back(pairs[i].first);
    }
    return topTen;
}

vector<int> MoviesService::getComparableUsers(int userID, int movieID) {
    Database *db = StateManager::getInstance()->getDb();
    vector<int> comparableUsers;
    //Gets all known users in our database
    auto allUsers = db->getAllUserIds();
    for (int i: allUsers) {
        //Checks whether the current user has the asked movie, also makes sure it's not the user that made the request
        if (db->userHasMovie(i, movieID) && i != userID) {
            //Assuming the user fits, adds them to the vector of fitting users
            comparableUsers.push_back(i);
        }
    }
    return comparableUsers;
}

vector<int> MoviesService::rankComparableUsers(int userID, vector<int> *comparedUsers) {
    Database *db = StateManager::getInstance()->getDb();
    //Initializes a vector with the size of the user count, with all values at 0
    vector<int> userRanks(comparedUsers->size(), 0);
    //Runs in a loop, with I being each movie the original user watched
    for (int i: db->getUserMovies(userID)) {
        //Another loop where J runs on the size of all comparable users
        for (int j = 0; j < comparedUsers->size(); j++) {
            //Adds 1 to each user's comparison "rank" (the weight the user will have in the recommendation algorithm)
            //For each shared movie they have to the original user
            if (db->userHasMovie((*comparedUsers)[j], i)) {
                userRanks.at(j)++;
            }
        }
    }
    return userRanks;
}

map<int, int> MoviesService::mapComparableMovies(int userID, int movieID, vector<int> *users, vector<int> *ranks) {
    Database *db = StateManager::getInstance()->getDb();
    map<int, int> movieMap;
    //Runs over the user's ranks list
    int k = 0;
    //For each user comparable to the original user
    for (int i: *users) {
        if (ranks->at(k) == 0) {
            //If the user's rank is 0, he's not relevant, skips his watched movies
            k++;
            continue;
        }
        //Initializes a new vector containing all the movies the current user has watched
        vector<int> userMovies = db->getUserMovies(i);
        //For each movieID in the current user's watched movies list
        for (int j: userMovies) {
            //In case the original user has watched the movie or if it's the asked about movie
            //we will not add it to the recommendation map
            if (db->userHasMovie(userID, j) || j == movieID) {
                continue;
            }
            //In case the movie isn't in the map yet, we will add it
            if (movieMap.find(j) == movieMap.end()) {
                movieMap.emplace(j, ranks->at(k));
            }
                //Otherwise, meaning both that the OG user hasn't watched it, and it is already somewhere in the map
                //We will add to its recommendation value the user's rank
            else {
                movieMap[j] += ranks->at(k);
            }
        }
        k++;
    }
    return movieMap;
}


