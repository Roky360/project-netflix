#include "InvalidRequest.h"
#include "../Response.h"

InvalidRequest::InvalidRequest() : Request() {
}

string InvalidRequest::getHelpMsg() {
    return "";
}

Response *InvalidRequest::execute() {
    // create new invalid request response and return it
    return new Response(BAD_REQUEST_400, this->context);
};
