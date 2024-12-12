#include "Request.h"
#include "invalid_request/InvalidRequest.h"
#include "../app/StateManager.h"
#include <map>
#include <utility>

using namespace app;

Request *Request::fromName(const string &reqName, vector<string> args, ClientContext* cl) {
    // get the state manager
    auto manager = StateManager::getInstance();

    // get the map
    auto map = manager->getRequestMap();

    // if he didn't find the request
    if (map.find(reqName) == map.end()) {
        return new InvalidRequest({}, cl);
    }

    // return the wanted request
    return map[reqName](std::move(args), cl);
}

Request::Request() : args({}), context(nullptr) {
}
