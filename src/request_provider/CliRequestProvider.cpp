#include "CliRequestProvider.h"
#include "../request/Request.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

Request* CliRequestProvider:: nextRequest() {

    vector<string> args; // holds the arguments of the request
    string str; // hold the input from the user
    string reqName; // holds the request name

    // get the wanted request from the user
    getline(cin, str);

    // Use a string stream to parse the input string
    stringstream ss(str);

    // get the first word as the request name
    ss >> reqName;

    // read the rest of the line and enter them to args
    string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }

    return Request::fromName(reqName, args);
};
