#include "StateManager.h"

namespace app {
    StateManager *StateManager::instance = nullptr;

    StateManager::~StateManager() {
        delete db;
        delete rp;
    }

    StateManager *StateManager::getInstance() {
        if (instance == nullptr) {
            instance = new StateManager();
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

#include "StateManager.h"

#include <utility>
