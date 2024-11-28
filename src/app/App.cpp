#include <iostream>
#include "App.h"
#include "StateManager.h"
#include "../request/Response.h"
#include "../request/Request.h"
#include "../request_Provider/RequestProvider.h"

namespace app {
    void App::run() {
        auto *sm = StateManager::getInstance();
        RequestProvider *rp = sm->getRequestProvider();

        while (true) {
            Request *request = rp->nextRequest();
            Response *response = request->execute();

            if (!response->payload.empty()) {
                cout << response->payload << endl;
            }
        }
    }
} // app