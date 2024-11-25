#include "app/App.h"
#include "app/StateManager.h"
#include "database/FilesDatabase.h"
#include "Request/AddMovieRequest.h"
#include "Request/HelpRequest.h"
#include "Request/RecommendMovieRequest.h"
#include "Request_Provider/CliRequestProvider.h"

using namespace app;
using namespace db;

int main() {
    map<string, requestGen> requestMap = {
        {"add", [](auto args) -> Request *{ return new AddMovieRequest(args); }},
        {"recommend", [](auto args) -> Request *{ return new RecommendMovieRequest(args); }},
        {"help", [](auto args) -> Request *{ return new HelpRequest(args); }},
    };

    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());
    sm->setRequestMap(requestMap);
    sm->setRequestProvider(new CliRequestProvider());

    auto *app = new App();
    app->run();

    delete app;
    delete sm;
    return 0;
}
