#include "HelpRequest.h"
#include <iostream>

using namespace std;

HelpRequest::HelpRequest(const vector<string> &args) : Request(args) {
}

Response *HelpRequest::execute() {
    // if the user entered arguments - return invalid request.
    if (!args.empty()) {
        return new Response(INVALID_ARG, "invalid arg.");
    }

    // the menu
    string menu = "add [userid] [movieid1] [movieid2]...\nrecommand [userid] [movieid]\nhelp";

    // return the response
    return new Response(OK, "", menu);
}
