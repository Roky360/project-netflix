#ifndef PROJECT_NETFLIX_DATABASE_H
#define PROJECT_NETFLIX_DATABASE_H

#include <vector>

using namespace std;

namespace db {
    /**
     * An interface for a database class that provides storage services to the system.
     */
    class Database {
    protected:
        // make the constructor unreachable from outside since this is an interface
        Database() = default;
    public:
        virtual ~Database() = default;

        /**
         * Marks a `movieId` as watched by a user.
         *
         * @param userId The user ID to add the movie to.
         * @param movieId The ID of the movie to add.
         */
        virtual void addMovieToUser(int userId, int movieId) = 0;

        /**
         * Returns a list of movie IDs watched by a `userId`.
         *
         * @param userId ID of the desired user.
         * @return An array containing the watched movie IDs.
         */
        virtual vector<int> getUserMovies(int userId) = 0;

        /**
         * Returns a list of all the User IDs currently stored in the Databse.
         *
         * @return A list of all the stored User IDs.
         */
        virtual vector<int> getAllUserIds() = 0;
    };
} // db

#endif //PROJECT_NETFLIX_DATABASE_H
