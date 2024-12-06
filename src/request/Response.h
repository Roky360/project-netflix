#ifndef PROJECT_NETFLIX_RESPONSE_H
#define PROJECT_NETFLIX_RESPONSE_H
#include <string>
#include "../client_context/ClientContext.h"
#include <map>
using namespace std;

enum Status {
    OK_200,                 // value 0
    CREATED_201,            // value 1
    NO_CONTENT_204,         // value 2
    BAD_REQUEST_400,        // value 3
    NOT_FOUND_404           // value 4
};

/**
 * Response object that contains the result of a request.
 */
class Response {
public:
    // fields
    Status status;
    string payload;
    ClientContext* context;

    // default constructor
    Response() : status(OK_200), payload("") {}

    // constructor
    Response(Status s, ClientContext* cl, const string &payload = "") : status(s), context(cl), payload(payload){}

    /**
     * return string that contains the status string + payload
     * @return answer from the server in string
     */
    string toRawData();

private:
    static const map<Status, string> statusMap;
};


#endif
