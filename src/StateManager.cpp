//
// Created by avi on 11/22/2024.
//
#include "StateManager.h"

StateManager *StateManager::instance = nullptr;


StateManager *StateManager::getInstance() {
    if (instance == nullptr) {
        instance = new StateManager();
    }
    return instance;
}

Database *StateManager::getDb() {
    return db;
}

void StateManager::setDb(int *db) {
    this->db = db;
}

RequestProvider *StateManager::getRequestProvider() {
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


#include "StateManager.h"

#include <utility>
