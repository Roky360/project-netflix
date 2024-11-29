#include <gtest/gtest.h>
#include "../src/database/FilesDatabase.h"
#include <string>
#include <fstream>

using namespace db;
using namespace std;

/// A helper function that reads the db file contents to compare output in the tests.
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

/// A helper function that returns a string representation of an int array.
string intArrToString(const vector<int> &arr) {
    string s = "[";
    for (auto elem: arr) {
        s += to_string(elem) + " ";
    }
    if (s.length() == 1)
        s += "]";
    else
        s = s.substr(0, s.length() - 1) + "]";
    return s;
}

TEST(FilesDbTests, addMovieTouser_SanityTest) {
    auto *db = new FilesDatabase();

    db->addMovieToUser(104, 1001);
    db->addMovieToUser(104, 1002);
    db->addMovieToUser(102, 1001);
    db->addMovieToUser(105, 1008);
    db->addMovieToUser(102, 1009);
    db->addMovieToUser(104, 1001);

    EXPECT_EQ(readDbFile(), "104 1001 1002\n102 1001 1009\n105 1008");

    delete db;
}

TEST(FilesDbTests, getUserMovies_SanityTest) {
    auto *db = new FilesDatabase();

    EXPECT_EQ(intArrToString(db->getUserMovies(104)), intArrToString({1001, 1002}));
    EXPECT_EQ(intArrToString(db->getUserMovies(102)), intArrToString({1001, 1009}));
    EXPECT_EQ(intArrToString(db->getUserMovies(105)), intArrToString({1008}));
    EXPECT_EQ(intArrToString(db->getUserMovies(1001)), intArrToString({}));

    EXPECT_EQ(intArrToString(db->getAllUserIds()), intArrToString({105, 102, 104}));

    delete db;
}

TEST(FilesDbTests, userMethods_SanityTest) {
    auto *db = new FilesDatabase();

    EXPECT_EQ(db->getAllUserIds(), (vector<int>){});

    db->addMovieToUser(1, 101);
    db->addMovieToUser(1, 101);
    db->addMovieToUser(1, 102);
    db->addMovieToUser(3, 103);
    db->addMovieToUser(2, 103);

    EXPECT_EQ(db->getAllUserIds(), vector<int>({2,3,1}));

    delete db;
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
