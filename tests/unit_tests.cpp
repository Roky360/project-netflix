#include <gtest/gtest.h>

#include "general_tests.h"
#include "files_db_tests.h"
#include "recommendation_algo_tests.h"

#include "../src/app/StateManager.h"
#include "../src/database/files_database/FilesDatabase.h"
#include "../src/request/all_requests.h"

using namespace app;
using namespace db;

int main(int argc, char **argv) {
    const map<string, requestGen> requestMap = {
        {"help", [](auto args, auto c) -> Request *{ return new HelpRequest(args, {}); }},
        {"recommend", [](auto args, auto c) -> Request *{ return new GetRequest(args, {}); }},
        {"add", [](auto args, auto c) -> Request *{ return new PostRequest(args, {}); }},
    };
    // init state manager with necessary data
    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());
    sm->setRequestMap(requestMap);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
