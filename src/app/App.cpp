#include <iostream>
#include "App.h"
#include "StateManager.h"
#include "../request/Response.h"
#include "../request/Request.h"
#include "../request_provider/RequestProvider.h"
#include "../request_executor/RequestExecutor.h"

namespace app {
    App::App(RequestProvider *provider, ResponseSender *sender, RequestExecutor *executor) {
        rp = provider;
        rs = sender;
        re = executor;
    }

    void App::run() {
        auto *sm = StateManager::getInstance();

        while (true) {
            Request *request = rp->nextRequest();

            // if there was a problem in the server, continue to the next
            if (request == nullptr) {
                continue;
            }
            re->execute(request);

        }
    }
} // app