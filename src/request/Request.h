#ifndef PROJECT_NETFLIX_REQUEST_H
#define PROJECT_NETFLIX_REQUEST_H

#include "Response.h"
#include "../client_context/ClientContext.h"
#include <string>
#include <vector>

class Request {
public:
    // the arguments of the request
    vector<string> args;
    // the client context of the request
    ClientContext* context;

    explicit Request(const vector<string> &args, ClientContext* cl) : args(args), context(cl) {}

    Request();

    virtual ~Request() = default;

    /**
     * Returns a help message that describes how to use this command.
     * A help request should display the help messages of all available commands.
     * @return A help message describing how to use this command.
     */
    virtual string getHelpMsg() = 0;

    /**
     * execute the wanted action
     * @return response
     */
    virtual Response *execute() = 0;

    /**
     * return the wanted request
     * @param reqName the request name
     * @param args the arguments of the request
     * @param cl the client context
     * @return the wanted request
     */
    static Request *fromName(const string &reqName, vector<string> args, ClientContext* cl);
};

#endif
