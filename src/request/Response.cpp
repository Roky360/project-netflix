#include "Response.h"

string Response::toRawData() {

    // the string that will be returned
    string str;

    // switch the status cases and enter the string accordingly
    switch (status) {
        case OK_200:
            str = "200 OK";
            break;

        case CREATED_201:
            str = "201 Created";
            break;

        case NO_CONTENT_204:
            str = "204 NO Content";
            break;

        case BAD_REQUEST_400:
            str = "400 Bad Request";
            break;

        case NOT_FOUND_404:
            str = "404 Not Found";
            break;
    }

    // if the response payload is not empty add it to the string
    if(!this->payload.empty()) {
        str += "\n\n" + this->payload;
    }

    // return the string
    return str;

}