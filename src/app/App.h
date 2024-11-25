#ifndef PROJECT_NETFLIX_APP_H
#define PROJECT_NETFLIX_APP_H

namespace app {
    /**
     * Runs and manages the main routine of the application.
     */
    class App {
    public:
        App() = default;

        ~App() = default;

        /**
         * Runs the main loop of handling requests.
         * * Assumes that the `StateManager` is initialized with proper values.
         */
        void run();
    };

} // app

#endif //PROJECT_NETFLIX_APP_H
