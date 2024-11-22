#include "app/App.h"
#include "app/StateManager.h"
#include "database/FilesDatabase.h"

using namespace app;
using namespace db;

int main() {
    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());
    // TODO: initialize StateManager

    auto *app = new App();
    app->run();

    delete app;
    delete sm;
    return 0;
}
