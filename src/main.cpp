#include "app/App.h"
#include "app/StateManager.h"
#include "database/FilesDatabase.h"
#include "request/AddMovieRequest.h"
#include "request/HelpRequest.h"
#include "request/RecommendMovieRequest.h"
#include "request_Provider/CliRequestProvider.h"

using namespace app;
using namespace db;

int main() {
    // initialize supported requests map
    map<string, requestGen> requestMap = {
        {"add", [](auto args) -> Request *{ return new AddMovieRequest(args); }},
        {"recommend", [](auto args) -> Request *{ return new RecommendMovieRequest(args); }},
        {"help", [](auto args) -> Request *{ return new HelpRequest(args); }},
    };
    // Initialize app state
    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());
    sm->setRequestMap(requestMap);
    sm->setRequestProvider(new CliRequestProvider());

    // Run app
    auto *app = new App();
    app->run();

    delete sm;
    delete app;
    return 0;
}
