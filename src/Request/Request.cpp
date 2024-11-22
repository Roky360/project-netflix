#include "Request.h"
#include "HelpRequest.h"
#include "InvalidRequest.h"
#include "../app/StateManager.h"
#include <map>

using namespace app;

Request* Request::fromName(const string& reqName, vector<string> args) {
    // get the state manager
    auto manager = StateManager::getInstance();

    // get the map
    auto map = manager->getRequestMap();

    // if he didnt find the request
    if (map.find(reqName) == map.end())  {
        return new InvalidRequest();
    }

    // return the wanted request
    return map[reqName](args);
}
