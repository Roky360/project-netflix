#ifndef PROJECT_NETFLIX_REQUEST_H
#define PROJECT_NETFLIX_REQUEST_H
#include "Response.h"
#include <string>
#include <vector>
class Request {

    public:
        vector<string> args;

        virtual Response* execute() = 0;

        static Request* fromName(const string& reqName, vector<string> args);

};

#endif
