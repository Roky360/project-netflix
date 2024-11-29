#include "HelpRequest.h"

using namespace std;

HelpRequest::HelpRequest(const vector<string> &args) : Request(args) {
}

HelpRequest::HelpRequest() : Request() {
}

Response *HelpRequest::execute() {
    // if the user entered arguments - return invalid request.
    if (!args.empty()) {
        return new Response(INVALID_ARG, "invalid arguments.");
    }

    // the menu
    string menu = "add [userid] [movieid1] [movieid2]...\nrecommand [userid] [movieid]\nhelp";

    // return the response
    return new Response(OK, "", menu);
}
