#include "app/App.h"
#include "app/StateManager.h"
#include "database/FilesDatabase.h"
#include "request_provider/socket_provider/SocketRequestProvider.h"
#include "request/all_requests.h"

using namespace app;
using namespace db;

int main() {
    // initialize supported requests map
    const map<string, requestGen> requestMap = {
            {"help", [](auto args, auto cl) -> Request *{ return new HelpRequest(args, cl); }},
            {"GET", [](auto args, auto cl) -> Request *{ return new GetRequest(args, cl); }},
            {"DELETE", [](auto args, auto cl) -> Request *{ return new DeleteRequest(args, cl); }},
            {"PATCH", [](auto args, auto cl) -> Request *{ return new PatchRequest(args, cl); }},
            {"POST", [](auto args, auto cl) -> Request *{return new PostRequest(args, cl); }},
    };
    // Initialize app state
    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());
    sm->setRequestMap(requestMap);
    sm->setRequestProvider(new SocketRequestProvider(20200, "127.0.0.1", 10));

    // Run app
    auto *app = new App();
    app->run();

    delete app;
    delete sm;
    return 0;
}
