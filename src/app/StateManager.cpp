#include "StateManager.h"

#include <unordered_map>

namespace app {
    StateManager *StateManager::instance = nullptr;

    StateManager::~StateManager() {
        delete db;
        delete rp;
    }

    StateManager *StateManager::getInstance() {
        // thread-safely for accessing the singleton instance
        if (instance == nullptr) {
            auto *pm = PermissionManager::getInstance();
            pm->requestWrite();
            if (instance == nullptr) {
                instance = new StateManager();
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

    unordered_map<string, requestGen> StateManager::getRequestMap() {
        return mapRequest;
    }

    void StateManager::setRequestMap(unordered_map<string, requestGen> reqMap) {
        mapRequest = std::move(reqMap);
    }
}
