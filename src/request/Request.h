#ifndef PROJECT_NETFLIX_REQUEST_H
#define PROJECT_NETFLIX_REQUEST_H
#include "Response.h"
#include <string>
#include <vector>

class Request {
public:
    // the arguments of the request
    vector<string> args;

    explicit Request(const vector<string> &args) : args(args) {}

    Request();

    virtual ~Request() = default;

    /**
     * execute the wanted action
     * @return response
     */
    virtual Response *execute() = 0;

    /**
     * return the wanted request
     * @param reqName the request name
     * @param args the arguments of the request
     * @return the wanted request
     */
    static Request *fromName(const string &reqName, vector<string> args);
};

#endif
