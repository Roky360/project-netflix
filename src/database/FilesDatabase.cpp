#include "FilesDatabase.h"

namespace db {
    const string FilesDatabase::DB_FILE_PATH = "../../db/data.db";

    void FilesDatabase::addMovieToUser(int userId, int movieId) {
        int x = 1;
    }

    vector<int> FilesDatabase::getUserMovies(int userId) {
        return {1};
    }
} // db