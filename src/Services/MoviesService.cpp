//
// Created by avi on 11/22/2024.
//

#include "MoviesService.h"
MoviesService *MoviesService::instance = nullptr;

MoviesService *MoviesService::getInstance() {
    if (instance == nullptr) {
        instance = new MoviesService();
        instance->db = StateManager::getInstance()->getDb();
    }
    return instance;
}

void MoviesService::addMovieToUser(int userID, int movieID) {
    db->addMovieToUser(userID, movieID);
}

vector<int> MoviesService::recommendMovies(int userID, int movieID) {

    vector<int> users = MoviesService::getComparableUsers(userID, movieID);
    vector<int> ranks = MoviesService::rankComparableUsers(userID, users);

}

vector<int> MoviesService::getComparableUsers(int userID, int movieID) {
    auto comparableUsers = new vector<int>;
    auto allUsers = db->getUserIds();
    for (int i : allUsers) {
        if (db->userHasMovie(i, movieID) == true && i != userID) {
            comparableUsers->push_back(i);
        }
    }
    return *comparableUsers;
}

vector<int> MoviesService::rankComparableUsers(int userID, vector<int> comparedUsers) {
    vector<int> userRanks(db->getUserCount(), 0);
    for(int i: db->getUserMovies(userID)) {
        for (int j : comparedUsers) {
            if (db->userHasMovie(comparedUsers.at(j), i)) {
                userRanks.at(0)++;
            }
        }
    }
    return userRanks;
}



