#include <gtest/gtest.h>
#include "../src/request_Provider/RequestProvider.h"
#include "../src/request_Provider/CliRequestProvider.h"
#include "../src/database/FilesDatabase.h"
#include "../src/request/HelpRequest.h"
#include "../src/request/AddMovieRequest.h"
#include "../src/app/StateManager.h"
#include <string>
#include <fstream>
#include <sstream>



using namespace db;
using namespace std;
using namespace app;

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

// test ask for help request
TEST(Request, helpRequest_sanityTest) {

    // create new help request
    Request* helpReq1 = new HelpRequest();

    // execute and get the response
    Response* res1 = helpReq1->execute();

    // check the response
    EXPECT_EQ(res1->payload, "add [userid] [movieid1] [movieid2]...\nrecommand [userid] [movieid]\nhelp");

    vector<string> vec = {"i cant", "be here"};

    // create new help request - with arguments
    Request* helpReq2 = new HelpRequest(vec);

    // execute and get the response
    Response* res2 = helpReq2->execute();

    // check the response
    EXPECT_EQ(res2->status, INVALID_ARG);
}

// test add request
TEST(Request, addMovieRequest_sanityTest) {

    // create add movie request with no arguments
    Request* addReq1 = new AddMovieRequest();
    Response* res1 = addReq1->execute();
    EXPECT_EQ(res1->status, INVALID_ARG);

    // create new add request with arguments
    vector<string> args = {"1", "100", "101", "102", "103"};
    string stringArgs = "1 100 101 102 103";
    Request* addReq2 = new AddMovieRequest(args);
    Response* res2 = addReq2->execute();

    // get the file context
    string fileStr = readDbFile();

    // check
    EXPECT_EQ(res2->status, OK);
    EXPECT_EQ(fileStr, stringArgs);
}

int main() {
    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}



