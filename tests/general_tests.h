#ifndef GENERAL_TESTS_H
#define GENERAL_TESTS_H

#include <gtest/gtest.h>
#include "utils/TestUtils.h"
#include "../src/database/files_database/FilesDatabase.h"
#include "../src/request/all_requests.h"

using namespace db;

/**
 * test for post request
 * this request is legal only if the user is not exist
 */
TEST(Request, postRequest_sanityTest) {
    remove(FilesDatabase::DB_FILE_PATH.c_str());

    // create new post request with arguments
    vector<string> args = {"5", "135", "137", "168", "376"};
    string stringArgs = "5 135 137 168 376";

    Request *postReq = new PostRequest(args, nullptr);
    Response *res = postReq->execute();

    // check
    EXPECT_EQ(res->status, CREATED_201);
    EXPECT_EQ(TestUtils::readDbFile(), stringArgs);

    args = {"5", "100", "300"};

    Request *postReq2 = new PostRequest(args, nullptr);
    Response *res2 = postReq2->execute();

    /**
     * test
     * post request execute only if it is new user
     * check with the same user and expect bad request
     */
    EXPECT_EQ(res2->status, BAD_REQUEST_400);
    EXPECT_EQ(TestUtils::readDbFile(), stringArgs);

    // create new post request with arguments
    vector<string> args3 = {"2", "100", "101", "102"};
    string stringArgs3 = "2 100 101 102";

    Request *postReq3 = new PostRequest(args3, nullptr);
    Response *res3 = postReq3->execute();

    /**
     * test
     * post request execute only if it is new user
     * created new request with new user and expect to have in the data the 2 users
     */
    EXPECT_EQ(res3->status, CREATED_201);
    EXPECT_EQ(TestUtils::readDbFile(), stringArgs + "\n" + stringArgs3);

    // cleanup
    remove(FilesDatabase::DB_FILE_PATH.c_str());
}

/**
 * patch request test
 * this request is legal only if the user already exist!
 * you can create user only with post request
 */
TEST(Request, patchRequest_sanityTest) {
    // first - lets create patch with not exist user and expect bad request
    Request *patchRec1 = new PatchRequest({"1", "100"}, nullptr);
    Response *res1 = patchRec1->execute();

    // expect NO CONTENT status and empty file
    EXPECT_EQ(res1->status, NOT_FOUND_404);
    EXPECT_EQ(TestUtils::readDbFile(), "");

    // create user using post
    Request *postReq2 = new PostRequest({"1", "100"}, nullptr);
    Response *postRes2 = postReq2->execute();

    // expect CREATED status and file with the arguments
    EXPECT_EQ(postRes2->status, CREATED_201);
    EXPECT_EQ(TestUtils::readDbFile(), "1 100");

    // create the user arguments
    vector<string> args2 = {"1", "100", "101", "102"};
    string stringArgs2 = "1 100 101 102";

    // create the patch request and execute
    Request *patchReq2 = new PatchRequest(args2, nullptr);
    Response *res2 = patchReq2->execute();

    // expect to status NO CONTENT and file with the args
    EXPECT_EQ(res2->status, NO_CONTENT_204);
    EXPECT_EQ(TestUtils::readDbFile(), stringArgs2);

    // cleanup
    remove(FilesDatabase::DB_FILE_PATH.c_str());
}

/**
 * test for delete request
 * delete only if the user exist and only if the user has those movies
 */
TEST(Request, deleteRequest_sanityTest) {
    // create new post request with arguments
    vector<string> args = {"5", "135", "137", "168", "376"};
    string stringArgs = "5 135 137 168 376";

    Request *postReq = new PostRequest(args, nullptr);
    Response *postRes = postReq->execute();

    // check
    EXPECT_EQ(postRes->status, CREATED_201);
    EXPECT_EQ(TestUtils::readDbFile(), stringArgs);

    // first test - delete movies to not exist user
    Request *delReq1 = new DeleteRequest({"1", "100", "105"}, nullptr);
    Response *delRes1 = delReq1->execute();

    // expect to not found status and the same context in the file
    EXPECT_EQ(delRes1->status, NOT_FOUND_404);
    EXPECT_EQ(TestUtils::readDbFile(), stringArgs);

    // second test - delete movie that the user dont have
    Request *delReq2 = new DeleteRequest({"5", "135", "168", "200"}, nullptr);
    Response *delRes2 = delReq2->execute();

    // expect to bad request and the same context in the file
    EXPECT_EQ(delRes2->status, BAD_REQUEST_400);
    EXPECT_EQ(TestUtils::readDbFile(), stringArgs);

    // third test - delete movies from the user
    Request *delReq3 = new DeleteRequest({"5", "135", "168"}, nullptr);
    Response *delRes3 = delReq3->execute();

    string expectString = "5 137 376";

    // expect to bad request and the same context in the file
    EXPECT_EQ(delRes3->status, NO_CONTENT_204);
    EXPECT_EQ(TestUtils::readDbFile(), expectString);

    // cleanup
    remove(FilesDatabase::DB_FILE_PATH.c_str());
}

#endif
