#include "app/App.h"
#include "app/StateManager.h"
#include "database/FilesDatabase.h"
#include "request_provider/socket_provider/SocketRequestProvider.h"
#include "request/all_requests.h"
#include "response_sender/socket_sender/SocketResponseSender.h"
#include "request_executor/threads_executor/ThreadRequestExecutor.h"

using namespace app;
using namespace db;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <port>" << endl;
        return 0;
    }
    int port;
    try {
        port = stol(argv[1]);
        if (port <= 0)
            throw invalid_argument("Port must be positive");
    } catch (invalid_argument &_) {
        cout << "Port must be a positive number" << endl;
        return 0;
    }

    // initialize supported requests map
    const map<string, requestGen> requestMap = {
        {"help", [](auto args, auto cl) -> Request *{ return new HelpRequest(args, cl); }},
        {"GET", [](auto args, auto cl) -> Request *{ return new GetRequest(args, cl); }},
        {"DELETE", [](auto args, auto cl) -> Request *{ return new DeleteRequest(args, cl); }},
        {"PATCH", [](auto args, auto cl) -> Request *{ return new PatchRequest(args, cl); }},
        {"POST", [](auto args, auto cl) -> Request *{ return new PostRequest(args, cl); }},
    };
    // Initialize app state
    auto *sm = StateManager::getInstance();
    sm->setDb(new FilesDatabase());
    sm->setRequestMap(requestMap);
    RequestProvider *rProvider = new SocketRequestProvider(port, "", 10);
    ResponseSender *rSender = new SocketResponseSender();
    RequestExecutor *rExecutor = new ThreadRequestExecutor(rSender, rProvider);
    // Run app
    auto *app = new App(rProvider, rSender, rExecutor);
    app->run();

    delete app;
    delete sm;
    return 0;
}
