#include "StateManager.h"

namespace app {
    bool StateManager::initialized = false;
    StateManager *StateManager::instance = nullptr;

    StateManager::~StateManager() {
        delete db;
        delete rp;
    }

    StateManager *StateManager::getInstance() {
        // thread-safely for accessing the singleton instance
        if (!initialized) {
            auto *pm = PermissionManager::getInstance();
            pm->requestWrite();
            if (!initialized) {
                instance = new StateManager();
                initialized = true;
            }
            pm->unlock();
        }
        return instance;
    }

    Database *StateManager::getDb() const {
        return db;
    }

    void StateManager::setDb(Database *db) {
        this->db = db;
    }

    RequestProvider *StateManager::getRequestProvider() const {
        return rp;
    }

    void StateManager::setRequestProvider(RequestProvider *rp) {
        this->rp = rp;
    }

    map<string, requestGen> StateManager::getRequestMap() {
        return mapRequest;
    }

    void StateManager::setRequestMap(map<string, requestGen> reqMap) {
        mapRequest = std::move(reqMap);
    }
}
