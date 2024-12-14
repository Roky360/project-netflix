#include "App.h"
#include "StateManager.h"
#include "../request/Request.h"
#include "../request_provider/RequestProvider.h"
#include "../request_executor/RequestExecutor.h"

namespace app {
    App::App(RequestProvider *provider, ResponseSender *sender, RequestExecutor *executor) {
        this->provider = provider;
        this->sender = sender;
        this->executor = executor;
    }

    App::~App() {
        delete this->provider;
        delete this->sender;
        delete this->executor;
    }

    void App::run() {
        while (true) {
            ClientContext *clientContext = provider->acceptClient();
            if (clientContext != nullptr) {
                executor->execute(clientContext);
            }
        }
    }
} // app
