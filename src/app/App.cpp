#include <iostream>
#include "App.h"
#include "StateManager.h"
#include "../request/Response.h"
#include "../request/Request.h"
#include "../request_provider/RequestProvider.h"

namespace app {
    void App::run() {
        auto *sm = StateManager::getInstance();
        RequestProvider *rp = sm->getRequestProvider();

        while (true) {
            Request *request = rp->nextRequest();

            // if there was a problem in the server, continue to the next
            if (request == nullptr) {
                continue;
            }

            Response *response = request->execute();

            if (!response->payload.empty()) {
                cout << response->payload << endl;
            }
        }
    }
} // app