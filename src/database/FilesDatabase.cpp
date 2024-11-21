#include <fstream>
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
            if (spaceIdx == string::npos)
                continue;
            string uid = line.substr(0, spaceIdx); // get user id (first word)
            this->uidToLineMap[uid] = i;
            i++;
        }
    }
    // TODO: not working!!
    void FilesDatabase::addMovieToUser(string userId, string movieId) {
        // user id doesnt exist
        if (this->uidToLineMap.find(userId) == this->uidToLineMap.end()) {
            this->uidToLineMap[userId] = this->uidToLineMap.size();

            ofstream f;
            f.open(DB_FILE_PATH, ios_base::app);
            f << userId + " " + movieId << '\n';
            f.close();
        } else {
            int lineNum = this->uidToLineMap[userId];
            fstream f(DB_FILE_PATH);
            string line;
            // all file contents
            string content((istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
            f.seekg(0);

            // skip all lines until the line of the desired user
            size_t startOfLinePos = 0;
            for (int i = 0; i <= lineNum; ++i) {
                getline(f, line);
                startOfLinePos += line.length() + 1;
            }
            // read user's line and add the movieId to it

            content.erase(startOfLinePos, line.length()); // remove old line

            line.insert(line.length(), " " + movieId);
            // override the user's line with the updated line
            content.insert(startOfLinePos, line);

            // write updated contents (rewrite file)
            f.seekp(0);
            f << content;

            f.close();
        }
    }

    vector<int> FilesDatabase::getUserMovies(string userId) {
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
        vector<string> movieIdsStr = Utils::split(line, " ");
        vector<int> movieIds;
        movieIds.reserve(movieIdsStr.size());
        // convert each element to int
        for (const auto &id: movieIdsStr) {
            movieIds.push_back(stoi(id));
        }

        return movieIds;
    }
} // db