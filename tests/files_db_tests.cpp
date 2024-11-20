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
        buff << line;
    }
    return buff.str();
}

bool compareArrays(const vector<int> &v1, const vector<int> &v2) {
    if (v1.size() != v2.size()) return false;
    for (int i = 0; i < v1.size(); ++i) {
        if (v1[i] != v2[i]) return false;
    }
    return true;
}

TEST(FilesDbTests, addMovieTouser_SanityTest) {
    auto *db = new FilesDatabase();

    db->addMovieToUser(104, 1001);
    EXPECT_EQ(readDbFile(), "104 1001");

    db->addMovieToUser(104, 1002);
    EXPECT_EQ(readDbFile(), "104 1001 1002");

    db->addMovieToUser(102, 1001);
    EXPECT_EQ(readDbFile(), "104 1001 1002\n102 1001");

    db->addMovieToUser(105, 1008);
    EXPECT_EQ(readDbFile(), "104 1001 1002\n102 1001\n105 1008");

    db->addMovieToUser(102, 1009);
    EXPECT_EQ(readDbFile(), "104 1001 1002\n102 1001 1009\n105 1008");

    delete db;
}

TEST(FilesDbTests, getUserMovies_SanityTest) {
    auto *db = new FilesDatabase();

    EXPECT_TRUE(compareArrays(db->getUserMovies(104), {1001, 1002}));
    EXPECT_TRUE(compareArrays(db->getUserMovies(102), {1001, 1009}));
    EXPECT_TRUE(compareArrays(db->getUserMovies(105), {1008}));
    EXPECT_TRUE(compareArrays(db->getUserMovies(1001), {}));

    delete db;
}

int main() {
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
