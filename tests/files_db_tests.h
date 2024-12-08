#ifndef FILES_DB_TESTS_H
#define FILES_DB_TESTS_H

#include <gtest/gtest.h>
#include "../src/database/FilesDatabase.h"
#include "utils/TestUtils.h"
#include "../src/utils/Utils.h"

using namespace db;

TEST(FilesDbTests, addMovieToUser_SanityTest) {
    auto *db = new FilesDatabase();

    // check if no users exist
    EXPECT_EQ(db->getAllUserIds(), (vector<int>){});

    db->addMovieToUser(104, 1001);
    db->addMovieToUser(104, 1002);
    db->addMovieToUser(102, 1001);
    db->addMovieToUser(105, 1008);
    db->addMovieToUser(102, 1009);
    db->addMovieToUser(104, 1001);

    EXPECT_EQ(TestUtils::readDbFile(), "104 1001 1002\n102 1001 1009\n105 1008");

    // cleanup
    delete db;
}

TEST(FilesDbTests, getUserMovies_SanityTest) {
    auto *db = new FilesDatabase();

    EXPECT_EQ(TestUtils::intArrToString(db->getUserMovies(104)), TestUtils::intArrToString({1001, 1002}));
    EXPECT_EQ(TestUtils::intArrToString(db->getUserMovies(102)), TestUtils::intArrToString({1001, 1009}));
    EXPECT_EQ(TestUtils::intArrToString(db->getUserMovies(105)), TestUtils::intArrToString({1008}));
    EXPECT_EQ(TestUtils::intArrToString(db->getUserMovies(1001)), TestUtils::intArrToString({}));

    EXPECT_EQ(TestUtils::intArrToString(db->getAllUserIds()), TestUtils::intArrToString({105, 102, 104}));

    // cleanup
    remove(FilesDatabase::DB_FILE_PATH.c_str());
    delete db;
}

TEST(FilesDbTests, userMethods_SanityTest) {
    auto *db = new FilesDatabase();

    // expect to all the users created in the previous tests
    EXPECT_EQ(db->getAllUserIds(), vector<int>({}));
    EXPECT_EQ(db->getUserCount(), 0);

    db->addMovieToUser(1, 101);
    db->addMovieToUser(1, 101);
    db->addMovieToUser(1, 102);
    db->addMovieToUser(3, 103);
    db->addMovieToUser(2, 103);

    // check if new users added correctly
    EXPECT_EQ(db->getAllUserIds(), vector<int>({2,3,1}));
    EXPECT_EQ(db->getUserCount(), 3);
    EXPECT_EQ(db->userHasMovie(1, 102), true);
    EXPECT_EQ(db->userHasMovie(2, 1), false);
    EXPECT_EQ(db->userHasMovie(1001, 102), false);

    // cleanup
    remove(FilesDatabase::DB_FILE_PATH.c_str());
    delete db;
}

TEST(FilesDbTests, deleteMovieFromUser_tests) {
    auto *db = new FilesDatabase();

    // check that there are no users
    EXPECT_EQ(db->getAllUserIds(), (vector<int>){});

    // add some movies
    db->addMovieToUser(104, 1001);
    db->addMovieToUser(104, 1002);
    db->addMovieToUser(102, 1001);
    db->addMovieToUser(105, 1008);
    db->addMovieToUser(102, 1009);
    db->addMovieToUser(104, 1001);
    EXPECT_EQ(TestUtils::readDbFile(), "104 1001 1002\n102 1001 1009\n105 1008");

    // delete one movie
    db->deleteMovieFromUser(102, 1009);
    EXPECT_EQ(TestUtils::readDbFile(), "104 1001 1002\n102 1001\n105 1008");

    // delete all movies
    db->deleteMovieFromUser(102, 1001);
    db->deleteMovieFromUser(104, 1001);
    db->deleteMovieFromUser(105, 1008);
    db->deleteMovieFromUser(104, 1001);
    db->deleteMovieFromUser(104, 1002);
    EXPECT_EQ(TestUtils::readDbFile(), "104\n102\n105");

    // add back movie after all have been deleted
    db->addMovieToUser(102, 1111);
    EXPECT_EQ(TestUtils::readDbFile(), "104\n102 1111\n105");

    // cleanup
    remove(FilesDatabase::DB_FILE_PATH.c_str());
    delete db;
}

TEST(FilesDbTests, usersWatched_tests) {
    auto *db = new FilesDatabase();

    // check that there are no users
    EXPECT_EQ(db->getAllUserIds(), (vector<int>){});

    // add some movies
    db->addMovieToUser(104, 1001);
    db->addMovieToUser(104, 1002);
    db->addMovieToUser(102, 1001);
    db->addMovieToUser(105, 1008);
    db->addMovieToUser(102, 1009);
    db->addMovieToUser(104, 1001);
    EXPECT_EQ(TestUtils::intArrToString(db->usersWatched(1001)), TestUtils::intArrToString({102, 104}));

    // delete one movie
    db->deleteMovieFromUser(102, 1001);
    EXPECT_EQ(TestUtils::intArrToString(db->usersWatched(1001)), TestUtils::intArrToString({104}));

    db->deleteMovieFromUser(104, 1001);
    EXPECT_EQ(TestUtils::intArrToString(db->usersWatched(1001)), TestUtils::intArrToString({}));

    // cleanup
    remove(FilesDatabase::DB_FILE_PATH.c_str());
    delete db;
}

#endif
