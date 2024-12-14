#ifndef PROJECT_NETFLIX_APP_H
#define PROJECT_NETFLIX_APP_H
#include "../request_provider/RequestProvider.h"
#include "../response_sender/ResponseSender.h"
#include "../request_executor/RequestExecutor.h"


namespace app {
    /**
     * Runs and manages the main routine of the application.
     */
    class App {
        RequestProvider *rp;
        ResponseSender *rs;
        RequestExecutor *re;
    public:
        App(RequestProvider *provider, ResponseSender *sender, RequestExecutor *executor);

        ~App() = default;

        /**
         * Runs the main loop of handling requests.
         * * Assumes that the `StateManager` is initialized with proper values.
         */
        void run();
    };

} // app

#endif //PROJECT_NETFLIX_APP_H
