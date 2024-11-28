#include <gtest/gtest.h>
#include "../src/request_Provider/RequestProvider.h"
#include "../src/request_Provider/CliRequestProvider.h"
#include "../src/database/FilesDatabase.h"
#include <string>
#include <fstream>
#include <sstream>



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

// test ask for help request
TEST(FilesDbTests, helpRequest_sanityTest) {

    string inputStr = "help\n";

    istringstream input(inputStr);

    cin.rdbuf(input.rdbuf());

    RequestProvider* rp = new CliRequestProvider();
    Request* rq = rp->nextRequest();

    ASSERT_NE(rq, nullptr);

    Response* res = rq->execute();

    ASSERT_NE(res, nullptr);

    EXPECT_EQ(res->payload, "add [userid] [movieid1] [movieid2]...\nrecommand [userid] [movieid]\nhelp\n");

    delete rp;
    delete rq;
    delete res;
}

// test add request
TEST(FilesDbTests, addMovieRequest_sanityTest) {

    string inputStr1 = "add 1 100 101 102 105\n";
    string inputStr1File = "1 100 101 102 105";

    istringstream input(inputStr1);

    cin.rdbuf(input.rdbuf());

    RequestProvider* rp = new CliRequestProvider();
    Request* rq = rp->nextRequest();

    Response* res = rq->execute();

    string fileStr = readDbFile();

    EXPECT_EQ(res->status, OK);
    EXPECT_EQ(fileStr, inputStr1File);
}


