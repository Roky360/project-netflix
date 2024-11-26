#include <gtest/gtest.h>
#include "../src/database/FilesDatabase.h"
#include "../src/services/MoviesService.h"
#include <string>
#include <fstream>

using namespace db;
using namespace std;

// A helper function that reads the db file contents to compare output in the tests.
string readDbFile() {
    ifstream f(FilesDatabase::DB_FILE_PATH);
    stringstream buff;
    string line;
    if (!f.good())
        return "";
    while (getline(f, line)) {
        buff << line << '\n';
    }
    string contents = buff.str();
    return contents.substr(0, contents.length() - 1);
}

string intArrToString(const vector<int> &arr) {
    string s;
    for (auto elem: arr) {
        s += to_string(elem) + " ";
    }
    return s;
}

TEST(recommendation_algo_tests, recommendMovies_SanityTest) {
auto *db = new FilesDatabase();

db->addMovieToUser(1, 100);
db->addMovieToUser(1, 102);
db->addMovieToUser(1, 101);
db->addMovieToUser(2, 100);
db->addMovieToUser(2, 103);
db->addMovieToUser(2, 104);
db->addMovieToUser(3, 100);
db->addMovieToUser(3, 101);
db->addMovieToUser(3, 104);
}