#ifndef PROJECT_NETFLIX_STATEMANAGER_H
#define PROJECT_NETFLIX_STATEMANAGER_H

#include <map>
#include <string>
#include <vector>

#include "PermissionManager.h"
#include "../database/Database.h"
#include "../request/Request.h"
#include "../request_provider/RequestProvider.h"

using namespace db;
using namespace std;

typedef Request *(*requestGen)(vector<string>, ClientContext*);

namespace app {
    /**
    * Singleton design pattern, state manager is responsible for connecting all the classes.
    * Holding important info such as the database or requests.
    */
    class StateManager {
        static bool initialized;
        static StateManager *instance;
        Database *db{};
        map<string, requestGen> mapRequest;
        RequestProvider *rp{};
        int server_port;

        StateManager() = default;

    public:
        ~StateManager();

        // Delete copy constructor and assignment operator to ensure a single instance
        StateManager(const StateManager &) = delete;

        StateManager &operator=(const StateManager &) = delete;

        /**
         * Returns a state manager, makes sure there is only one instance existing
         * at all times, Static method to provide global access
         * @return StateManager
         */
        static StateManager *getInstance();

        /**
         * Database Getter
         * @return db, Database
         */
        Database *getDb() const;

        /**
         * Database Setter
         * @param db Database
         */
        void setDb(Database *db);

        /**
         * RequestProvider Getter
         * @return RequestProvider
         */
        RequestProvider *getRequestProvider() const;

        /**
         * RequestProvide Setter
         * @param rp RequestProvider
         */
        void setRequestProvider(RequestProvider *rp);

        /**
         * RequestMap Getter
         * @return RequestMap
         */
        map<string, requestGen> getRequestMap();

        /**
         * RequestMap Setter
         * @param reqMap RequestMap
         */
        void setRequestMap(map<string, requestGen> reqMap);

        /**
         * server_port getter
         * @return the server port
         */
        int getServerPort();

        /**
         * server_port setter
         * @param port the new port
         */
        void setServerPort(int port);
    };
}

#endif //PROJECT_NETFLIX_STATEMANAGER_H
