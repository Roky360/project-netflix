#ifndef PROJECT_NETFLIX_RESPONSE_H
#define PROJECT_NETFLIX_RESPONSE_H
#include <string>
using namespace std;

enum Status {
    OK,             // value 0
    INVALID_ARG,    // value 1
    ERROR,          // value 2
    INVALID_REQUEST // value 3
};

/**
 * Response object that contains the result of a request.
 */
class Response {
public:
    // fields
    Status status;
    string errorMsg;
    string payload;

    // default constructor
    Response() : status(OK), errorMsg(""), payload("") {
    }

    // constructor
    Response(Status s, const string &error = "", const string &payload = "") : status(s), errorMsg(error),
                                                                               payload(payload) {
    }
};


#endif
