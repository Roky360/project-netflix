#ifndef PROJECT_NETFLIX_DATABASE_H
#define PROJECT_NETFLIX_DATABASE_H

#include <vector>

using namespace std;

namespace db {
    /**
     * An interface for a database class that provides storage services to the system.
     */
    class Database {
    public:
        /**
         * Marks a `movieId` as watched by a user.
         *
         * @param userId The user ID to add the movie to.
         * @param movieId The ID of the movie to add.
         */
        virtual void addMovieToUser(const string &userId, const string &movieId) = 0;

        /**
         * Returns a list of movie IDs watched by a `userId`.
         *
         * @param userId ID of the desired user.
         * @return An array containing the watched movie IDs.
         */
        virtual vector<int> getUserMovies(string userId) = 0;
    };
} // db

#endif //PROJECT_NETFLIX_DATABASE_H
