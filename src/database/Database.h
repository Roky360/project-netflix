#ifndef PROJECT_NETFLIX_DATABASE_H
#define PROJECT_NETFLIX_DATABASE_H

#include <vector>

using namespace std;

namespace db {
    /// An interface for a database class that provides storage services to the system.
    class Database {
    public:
        virtual void addMovieToUser(int userId, int movieId) = 0;

        virtual vector<int> getUserMovies(int userId) = 0;
    };
} // db

#endif //PROJECT_NETFLIX_DATABASE_H
