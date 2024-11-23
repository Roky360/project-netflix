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
    vector<int> ranks = MoviesService::rankComparableUsers(userID, &users);

    map<int, int> movieMap = mapComparableMovies(&users, &ranks);
    vector<pair<int, int>> pairs(movieMap.begin(), movieMap.end());

    std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    vector<int> topTen;
    int mini = min(10, (int) pairs.size());
    for (int i = 0; i < mini; ++i) {
        topTen.push_back(pairs[i].first);
    }

    return topTen;
}

vector<int> MoviesService::getComparableUsers(int userID, int movieID) {
    vector<int> comparableUsers;
    auto allUsers = db->getAllUserIds();
    for (int i : allUsers) {
        if (db->userHasMovie(i, movieID) && i != userID) {
            comparableUsers.push_back(i);
        }
    }
    return comparableUsers;
}

vector<int> MoviesService::rankComparableUsers(int userID, vector<int> *comparedUsers) {
    vector<int> userRanks(db->getUserCount(), 0);
    for(int i: db->getUserMovies(userID)) {
        for (int j = 0; j < comparedUsers->size(); j++) {
            if (db->userHasMovie((*comparedUsers)[j], i)) {
                userRanks.at(j)++;
            }
        }
    }
    return userRanks;
}

map<int, int> MoviesService::mapComparableMovies(vector<int> *users, vector<int> *ranks) {

    map<int, int> movieMap;
    int k = 0;
    for (int i : *users) {
        vector<int> userMovies = db->getUserMovies(i);
        for (int j : userMovies) {
            if (movieMap.find(j) == movieMap.end()) {
                movieMap.emplace(j, ranks->at(k));
            }
            else {
                movieMap[j] += ranks->at(k);
            }
        }
        k++;
    }
    return movieMap;
}


