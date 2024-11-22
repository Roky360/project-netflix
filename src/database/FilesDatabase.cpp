#include <fstream>
#include <sstream>
#include <algorithm>
#include "FilesDatabase.h"
#include "../utils/Utils.h"

using namespace utils;

namespace db {
    const string FilesDatabase::DB_FILE_PATH = "../data/data.db";

    FilesDatabase::FilesDatabase() {
        loadDbFile();
    }

    void FilesDatabase::loadDbFile() {
        ifstream f(DB_FILE_PATH);
        // if db file does not exist, create an empty one and return
        if (!f.good()) {
            ofstream f(DB_FILE_PATH);
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

    void FilesDatabase::addMovieToUser(int userId, int movieId) {
        ifstream inputFile(DB_FILE_PATH);
        vector<string> fileLines; // holds all the lines including the updated line, to be rewritten back to the db file
        string line;
        bool userFound = false;

        // read all lines
        while (getline(inputFile, line)) {
            istringstream iss(line);
            int currUserId;
            iss >> currUserId;

            // userId exists in the file
            if (currUserId == userId) {
                userFound = true;
                vector<int> movies;
                int movie;

                // read existing movie IDs
                while (iss >> movie) {
                    movies.push_back(movie);
                }

                // add the new movie if not already in the list
                if (find(movies.begin(), movies.end(), movieId) == movies.end()) {
                    movies.push_back(movieId);
                }

                // create the updated line
                ostringstream oss;
                oss << userId;
                for (const auto &m: movies) {
                    oss << " " << m;
                }
                line = oss.str();
            }

            fileLines.push_back(line);
        }
        inputFile.close();

        // if user was not found, add a new line for the user at the end of the file
        if (!userFound) {
            ostringstream oss;
            oss << userId << " " << movieId;
            fileLines.push_back(oss.str());
        }

        // rewrite all lines to the file
        ofstream outputFile(DB_FILE_PATH, ios::trunc);
        for (const auto &l: fileLines) {
            outputFile << l << "\n";
        }
        outputFile.close();
    }

    vector<int> FilesDatabase::getUserMovies(const int userId) {
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
        vector<string> movieIdsStr = Utils::split(line.substr(to_string(userId).length() + 1), " ");
        vector<int> movieIds;
        movieIds.reserve(movieIdsStr.size());
        // convert each element to int
        for (const auto &id: movieIdsStr) {
            movieIds.push_back(stoi(id));
        }

        return movieIds;
    }
} // db
