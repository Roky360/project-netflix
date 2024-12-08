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
         * Returns a list of all the User IDs currently stored in the Database.
         *
         * @return A list of all the stored User IDs.
         */
        virtual vector<int> getAllUserIds() = 0;

        /**
         * Returns the number of registered users in the Database.
         *
         * @return The number of registered users.
         */
        virtual int getUserCount() = 0;

        /**
         * Checks if a certain user has watched a certain movie.
         *
         * @param userId The ID of the user.
         * @param movieId The ID of the movie to check.
         * @return If the user has watched the movie.
         */
        virtual bool userHasMovie(int userId, int movieId) = 0;

        /**
         * Checks if a user is registered in the database.
         *
         * @param userId The ID of the user to check.
         * @return If the user exists.
         */
        virtual bool userExists(int userId) = 0;

        /**
         * Deletes a movie from a user (marks a movie as "unwatched").
         *
         * @param userId ID of the user to remove from.
         * @param movieId ID of the movie to remove.
         */
        virtual void deleteMovieFromUser(int userId, int movieId) = 0;
    };
} // db

#endif //PROJECT_NETFLIX_DATABASE_H
