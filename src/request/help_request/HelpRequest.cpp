#include "HelpRequest.h"

#include "../../app/StateManager.h"

using namespace std;
using namespace app;

HelpRequest::HelpRequest(const vector<string> &args) : Request(args) {
}

string HelpRequest::getHelpMsg() {
    return "help";
}

HelpRequest::HelpRequest() : Request() {
}

Response *HelpRequest::execute() {
    // if the user entered arguments - return invalid request.
    if (!args.empty()) {
        return new Response(INVALID_ARG, "invalid arguments.");
    }

    // iterate over all the available commands and get their help messages
    string menu;
    for (const auto &commands: StateManager::getInstance()->getRequestMap()) {
        Request *req = commands.second({});
        menu += req->getHelpMsg() + "\n";
        delete req;
    }
    if (!menu.empty())
        menu.erase(menu.end() - 1); // remove the last '\n'

    // return the response
    return new Response(OK, "", menu);
}
