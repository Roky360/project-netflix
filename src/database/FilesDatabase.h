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
    class FilesDatabase : public Database {
    public:
        static const string DB_FILE_PATH;

        // maps user id to its line in the database file
        unordered_map<int, int> uidToLineMap;

        explicit FilesDatabase();

        ~FilesDatabase() override = default;

        /* Methods */

        void loadDbFile();

        void addMovieToUser(int userId, int movieId) override;

        vector<int> getUserMovies(int userId) override;

        vector<int> getAllUserIds() override;

        int getUserCount() override;

        bool userHasMovie(int userId, int movieId) override;
    };
} // db

#endif //PROJECT_NETFLIX_FILESDATABASE_H
