#include "app/App.h"
#include "app/StateManager.h"
#include "database/FilesDatabase.h"
#include "request_provider/cli_provider/CliRequestProvider.h"
#include "request/all_requests.h"

using namespace app;
using namespace db;

int main() {
    // initialize supported requests map
    const unordered_map<string, requestGen> requestMap = {
            {"help", [](auto args) -> Request *{ return new HelpRequest(args); }},
            {"GET", [](auto args) -> Request *{ return new GetMovieRequest(args); }},
            {"add", [](auto args) -> Request *{ return new AddMovieRequest(args); }},
            {"patch", [](auto args) -> Request *{ return new PatchRequest(args); }},
    };
    // Initialize app state
    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());
    sm->setRequestMap(requestMap);
    sm->setRequestProvider(new CliRequestProvider());

    // Run app
    auto *app = new App();
    app->run();

    delete app;
    delete sm;
    return 0;
}
