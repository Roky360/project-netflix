#include "CliRequestProvider.h"
#include "../Request/Request.h"
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

    // read the rest of the line as arguments
    string arg;
    while (ss >> arg) {
        args.push_back(arg);
    }

    // Debug output
//    cout << "Full input: " << str << endl;
//    cout << "Request name: " << reqName << endl;
//    cout << "Arguments: ";
//    for (const string& a : args) {
//        cout << a << " ";
//    }
//    cout << endl;

    return Request::fromName(reqName, args);
};
