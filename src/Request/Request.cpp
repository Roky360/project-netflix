#include "Request.h"
#include "HelpRequest.h"
#include "InvalidRequest.h"
#include "StateManager.h"
#include <map>

Request* Request::fromName(const string& reqName, vector<string> args) {
    // get the state manager
    auto manager = StateManager::getInstance();

    // get the map
    auto map = manager->getMap();

    // if he didnt find the request
    if (map.find(reqName) == map.end())  {
        return new InvalidRequest();
    }

    // return the wanted request
    return map[reqName](args);
}
