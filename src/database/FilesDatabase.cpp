#include <fstream>
#include <sstream>
#include <algorithm>
#include "FilesDatabase.h"

#include "../app/PermissionManager.h"
#include "../utils/Utils.h"
// include libraries to use mkdir method
#ifdef _WIN32
#include <direct.h>  // Windows-specific
#define mkdir(path) _mkdir(path)
#else
    #include <sys/stat.h>  // Linux-specific
    #define mkdir(path) mkdir(path, 0755)
#endif

using namespace utils;
using namespace app;

namespace db {
    const string FilesDatabase::DB_DIRECTORY = "../data";
    const string FilesDatabase::DB_FILE_PATH = DB_DIRECTORY + "/data.db";

    FilesDatabase::FilesDatabase() {
        loadDbFile();
    }

    void FilesDatabase::loadDbFile() {
        ifstream f(DB_FILE_PATH);
        // if db file does not exist, create an empty one and return
        if (!f.good()) {
            mkdir(DB_DIRECTORY.c_str()); // create the DB directory if it doesn't exist
            f.close();
            return;
        }

        string line;
        int i = 0;
        // extract the user id (the first word) from each line and store it in the map with the line number
        while (getline(f, line)) {
            size_t spaceIdx = line.find(' ');
            if (spaceIdx == string::npos) // skip empty lines
                continue;
            // try to parse the user id. skip the line if failed
            try {
                int uid = stoi(line.substr(0, spaceIdx)); // get user id (first word)
                this->uidToLineMap[uid] = i;
                i++;
            } catch (invalid_argument &e) {
            }
        }
    }

    void FilesDatabase::updateLine(const int lineNum, string line) {
        PermissionManager::getInstance()->requestWrite();

        // if this line doesn't exist in the file yet
        if (lineNum == this->uidToLineMap.size()) {
            ofstream f;
            f.open(DB_FILE_PATH, ios_base::app); // open for appending
            f << line << "\n";
            f.close();
            PermissionManager::getInstance()->unlock();
            return;
        }

        ifstream dbIn(DB_FILE_PATH);
        vector<string> fileLines; // holds all the lines including the updated line, to be rewritten back to the db file
        string currLine;
        int currLineNum = 0;
        bool lineFound = false;

        // read all lines
        while (!lineFound && getline(dbIn, currLine)) {
            // found the line to be updated
            if (currLineNum == lineNum) {
                fileLines.push_back(line);

                // read remaining lines and finish the loop
                while (getline(dbIn, currLine)) {
                    fileLines.push_back(currLine);
                }
                lineFound = true;
            } else {
                fileLines.push_back(currLine);
                currLineNum++;
            }
        }
        dbIn.close();

        // rewrite all lines to the file
        ofstream dbOut(DB_FILE_PATH, ios::trunc);
        for (const auto &l: fileLines) {
            dbOut << l << "\n";
        }
        dbOut.close();

        PermissionManager::getInstance()->unlock();
    }

    void FilesDatabase::addMovieToUser(const int userId, const int movieId) {
        PermissionManager::getInstance()->requestWrite();

        string line; // updated line of the user
        int lineNum;

        // user doesn't exist -
        if (this->uidToLineMap.find(userId) == this->uidToLineMap.end()) {
            ostringstream oss;
            oss << userId << " " << movieId;
            line = oss.str();
            // add an entry to the map for the new user
            lineNum = this->uidToLineMap.size();
        } else {
            lineNum = this->uidToLineMap[userId];
            // user exists - add the movie to its line, if it's not already there
            vector<int> userMovies = this->getUserMovies(userId);
            // add the new movie if not already in the list
            if (find(userMovies.begin(), userMovies.end(), movieId) == userMovies.end()) {
                userMovies.push_back(movieId);
            }

            // create the updated line
            ostringstream oss;
            oss << userId;
            for (const auto &m: userMovies) {
                oss << " " << m;
            }
            line = oss.str();
        }

        // write the new line to the db file
        updateLine(lineNum, line);
        this->uidToLineMap[userId] = lineNum; // update user line number

        PermissionManager::getInstance()->unlock();
    }

    vector<int> FilesDatabase::getUserMovies(const int userId) {
        PermissionManager::getInstance()->requestRead();

        // user id does not exist - return empty array
        if (this->uidToLineMap.find(userId) == this->uidToLineMap.end()) {
            return {};
        }

        int lineNum = this->uidToLineMap[userId];
        string line;
        ifstream f(DB_FILE_PATH);
        if (!f.good())
            return {};

        // skip all lines until the desired line
        for (int i = 0; i < lineNum; ++i) {
            getline(f, line);
        }
        getline(f, line);

        // read all movie IDs to an array
        vector<string> movieIdsStr;
        if (line.length() > to_string(userId).length()) {
            // if the user HAS movies
            movieIdsStr = Utils::split(line.substr(to_string(userId).length() + 1), " ");
        }
        vector<int> movieIds;
        movieIds.reserve(movieIdsStr.size());
        // convert each element to int
        for (const auto &id: movieIdsStr) {
            movieIds.push_back(stoi(id));
        }

        PermissionManager::getInstance()->unlock();
        return movieIds;
    }

    vector<int> FilesDatabase::getAllUserIds() {
        PermissionManager::getInstance()->requestRead();

        vector<int> userIds;
        userIds.reserve(this->uidToLineMap.size());
        // iterate over the map and extract the keys which are the user IDs
        for (auto item: this->uidToLineMap) {
            userIds.push_back(item.first);
        }

        PermissionManager::getInstance()->unlock();
        return userIds;
    }

    int FilesDatabase::getUserCount() {
        PermissionManager::getInstance()->requestRead();
        const int count = this->uidToLineMap.size();
        PermissionManager::getInstance()->unlock();
        return count;
    }

    bool FilesDatabase::userHasMovie(const int userId, const int movieId) {
        auto userMovies = this->getUserMovies(userId);
        return find(userMovies.begin(), userMovies.end(), movieId) != userMovies.end();
    }

    bool FilesDatabase::userExists(const int userId) {
        PermissionManager::getInstance()->requestRead();
        const bool exists = this->uidToLineMap.find(userId) != this->uidToLineMap.end();
        PermissionManager::getInstance()->unlock();
        return exists;
    }

    void FilesDatabase::deleteMovieFromUser(const int userId, const int movieId) {
        PermissionManager::getInstance()->requestWrite();
        // if there is nothing to delete then return
        if (!userHasMovie(userId, movieId)) {
            PermissionManager::getInstance()->unlock();
            return;
        }

        // delete the movie from the user's movies
        vector<int> userMovies = this->getUserMovies(userId);
        userMovies.erase(find(userMovies.begin(), userMovies.end(), movieId));
        // build the updated line
        ostringstream newLine;
        newLine << userId;
        for (const auto movie: userMovies) {
            newLine << " " << movie;
        }
        // write the updated line to the db file
        updateLine(this->uidToLineMap[userId], newLine.str());

        PermissionManager::getInstance()->unlock();
    }
} // db
