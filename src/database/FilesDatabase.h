#ifndef PROJECT_NETFLIX_FILESDATABASE_H
#define PROJECT_NETFLIX_FILESDATABASE_H

#include "Database.h"
#include <iostream>

using namespace std;

namespace db {

    class FilesDatabase : Database {
    public:
        static const string DB_FILE_PATH; // TODO: move this to the State Manager

        explicit FilesDatabase() = default;

        void addMovieToUser(int userId, int movieId) override;

        vector<int> getUserMovies(int userId) override;
    };
} // db

#endif //PROJECT_NETFLIX_FILESDATABASE_H
