#ifndef RECOMMENDATION_ALGO_TESTS_H
#define RECOMMENDATION_ALGO_TESTS_H

#include <gtest/gtest.h>
#include "../src/services/MoviesService.h"
#include "../src/request/add_movie_request/AddMovieRequest.h"


TEST(recommendation_algo_tests, recommendMovies_Final) {
    MoviesService *ms = MoviesService::getInstance();
    //Sets the file to have users and movies
    vector<string> v1 = {"1", "100", "101", "102", "103"};
    auto *req1 = new AddMovieRequest(v1);
    req1->execute();
    vector<string> v2 = {"2", "101", "104", "105", "106", "102"};
    auto *req2 = new AddMovieRequest(v2);
    req2->execute();
    vector<string> v3 = {"3", "100", "104", "105", "107", "108"};
    auto *req3 = new AddMovieRequest(v3);
    req3->execute();
    vector<string> v4 = {"4", "101", "105", "106", "107", "110", "109"};
    auto *req4 = new AddMovieRequest(v4);
    req4->execute();
    vector<string> v5 = {"5", "100", "102", "103", "105", "108", "111"};
    auto *req5 = new AddMovieRequest(v5);
    req5->execute();
    vector<string> v6 = {"6", "100", "103", "104", "110", "111", "112", "113"};
    auto *req6 = new AddMovieRequest(v6);
    req6->execute();
    vector<string> v7 = {"7", "102", "105", "106", "107", "108", "109", "110"};
    auto *req7 = new AddMovieRequest(v7);
    req7->execute();
    vector<string> v8 = {"8", "101", "104", "105", "106", "109", "111", "114"};
    auto *req8 = new AddMovieRequest(v8);
    req8->execute();
    vector<string> v9 = {"9", "100", "103", "105", "107", "112", "113", "115"};
    auto *req9 = new AddMovieRequest(v9);
    req9->execute();
    vector<string> v10 = {"10", "100", "102", "105", "106", "107", "109", "110", "116"};
    auto *req10 = new AddMovieRequest(v10);
    req10->execute();
    // The example in the assignment
    vector<int> recResults1 = ms->recommendMovies(1, 104);
    vector<int> actResults1 = {105, 106, 111, 110, 112, 113, 107, 108, 109, 114};
    EXPECT_EQ(recResults1, actResults1);
    // Invalid input
    vector<int> recResults2 = ms->recommendMovies(11, 9);
    vector<int> actResults2 = {};
    EXPECT_EQ(recResults2, actResults2);
    vector<int> recResults3 = ms->recommendMovies(7, 116);
    vector<int> actResults3 = {100};
    EXPECT_EQ(recResults3, actResults3);

    // cleanup the created db file
    remove(FilesDatabase::DB_FILE_PATH.c_str());
}

#endif
