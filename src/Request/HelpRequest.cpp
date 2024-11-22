#include "HelpRequest.h"
#include <iostream>

using namespace std;

Response * HelpRequest::execute() {
    cout << "add [userid] [movieid1] [movieid2]..." << endl;
    cout << "recommand [userid] [movieid]" << endl;
    cout << "help" << endl;

    return new Response();
}
