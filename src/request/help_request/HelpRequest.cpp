#include "HelpRequest.h"

#include "../../app/StateManager.h"

using namespace std;
using namespace app;

HelpRequest::HelpRequest(const vector<string> &args, ClientContext* cl) : Request(args, cl) {}

string HelpRequest::getHelpMsg() {
    return "help";
}

HelpRequest::HelpRequest() : Request() {}

Response *HelpRequest::execute() {
    // if the user entered arguments - return invalid request.
    if (!args.empty()) {
        return new Response(BAD_REQUEST_400, this->context);
    }

    // iterate over all the available commands and get their help messages
    string menu;
    for (const auto &commands: StateManager::getInstance()->getRequestMap()) {
        Request *req = commands.second({}, nullptr);
        // if the request is help keep the msg and dont enter
        if (commands.first != "help") {
            menu += req->getHelpMsg() + "\n";
        }
        delete req;
    }

    // add the help message at the end
    if (!menu.empty()) {
        menu += "\n";
    }
    menu += this->getHelpMsg();

    if (!menu.empty()) {
        menu.erase(menu.end() - 1); // remove the last '\n'
    }

    // return the response
    return new Response(OK_200, this->context, menu);
}
