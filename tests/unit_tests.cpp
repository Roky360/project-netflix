#include <gtest/gtest.h>

#include "general_tests.h"
#include "files_db_tests.h"
#include "recommendation_algo_tests.h"

#include "../src/app/StateManager.h"
#include "../src/database/FilesDatabase.h"

using namespace app;
using namespace db;

int main(int argc, char **argv) {
    // init state manager with necessary data
    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
