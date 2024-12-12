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
        // Locks for reading
        auto *pm = PermissionManager::getInstance();
        pm->requestRead();
        Database *d = db;
        // Unlocks when finished reading
        pm->unlock();
        return d;
    }

    void StateManager::setDb(Database *db) {
        // Locks for writing
        auto *pm = PermissionManager::getInstance();
        pm->requestWrite();
        this->db = db;
        // Unlocks when finished writing
        pm->unlock();
    }

    RequestProvider *StateManager::getRequestProvider() const {
        // Locks for reading
        auto *pm = PermissionManager::getInstance();
        pm->requestRead();
        RequestProvider *r = rp;
        // Unlocks when finished reading
        pm->unlock();
        return r;
    }

    void StateManager::setRequestProvider(RequestProvider *rp) {
        // Locks for writing
        auto *pm = PermissionManager::getInstance();
        pm->requestWrite();
        this->rp = rp;
        // Unlocks when finished writing
        pm->unlock();
    }

    map<string, requestGen> StateManager::getRequestMap() {
        // Locks for reading
        auto *pm = PermissionManager::getInstance();
        pm->requestRead();
        map<string, requestGen> map = mapRequest;
        // Unlocks when finished reading
        pm->unlock();
        return map;
    }

    void StateManager::setRequestMap(map<string, requestGen> reqMap) {
        // Locks for writing
        auto *pm = PermissionManager::getInstance();
        pm->requestWrite();
        mapRequest = std::move(reqMap);
        // Unlocks when finished writing
        pm->unlock();
    }

    ResponseSender *StateManager::getResponseSender() {
        // Locks for reading
        auto *pm = PermissionManager::getInstance();
        pm->requestRead();
        ResponseSender *res = rs;
        // Unlocks when finished reading
        pm->unlock();
        return res;
    }

    void StateManager::setResponseSender(ResponseSender *sender) {
        // Locks for writing
        auto *pm = PermissionManager::getInstance();
        pm->requestWrite();
        this->rs = sender;
        // Unlocks when finished writing
        pm->unlock();
    }

}
