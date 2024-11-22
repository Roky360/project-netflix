#ifndef PROJECT_NETFLIX_FILESDATABASE_H
#define PROJECT_NETFLIX_FILESDATABASE_H

#include "Database.h"
#include <iostream>
#include <unordered_map>

using namespace std;

namespace db {
    /**
     * Allows saving data to a file.
     */
    class FilesDatabase : Database {
    private:
    public:
        // maps user id to its line in the database file
        unordered_map<string, int> uidToLineMap;

        void loadDbFile();

    public:
        static const string DB_FILE_PATH; // TODO: move this to the State Manager

        explicit FilesDatabase();

        void addMovieToUser(const string &userId, const string &movieId) override;

        vector<int> getUserMovies(string userId) override;
    };
} // db

#endif //PROJECT_NETFLIX_FILESDATABASE_H
