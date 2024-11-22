//
// Created by avi on 11/22/2024. BASSAD
//

#ifndef PROJECT_NETFLIX_STATEMANAGER_H
#define PROJECT_NETFLIX_STATEMANAGER_H
#include "database/Database.h"
#include <map>
#include <string>
#include <vector>
using namespace db;
using namespace std;
typedef Request(* requestGen)(vector<string>);

// Singleton design pattern, state manager is responsible for connecting all the classes
// Holding important info such as the database or requests
class StateManager {
public:
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
    Database *getDb();

    /**
     * Database Setter
     * @param db Database
     */
    void setDb(Database *db);

    /**
     * RequestProvider Getter
     * @return RequestProvider
     */
    RequestProvider *getRequestProvider();

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

private:
    //Fields
    static StateManager *instance;
    Database *db;
    map<string, requestGen> mapRequest;
    RequestProvider *rp;

    StateManager() = default;
};
#endif //PROJECT_NETFLIX_STATEMANAGER_H
