#include "HelpRequest.h"
#include <iostream>

using namespace std;

HelpRequest::HelpRequest(const vector<string> &args) : Request(args) {
}

Response *HelpRequest::execute() {
    // if the user entered arguments - return invalid request.
    if (!args.empty()) {
        return new Response(INVALID_REQUEST, "invalid request.");
    }

    // print the menu
    cout << "add [userid] [movieid1] [movieid2]..." << endl;
    cout << "recommand [userid] [movieid]" << endl;
    cout << "help" << endl;

    // return the response
    return new Response();
}
