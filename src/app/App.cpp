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
            ClientContext* clientContext = rp->acceptClient();

            re->execute(clientContext);
        }
    }
} // app