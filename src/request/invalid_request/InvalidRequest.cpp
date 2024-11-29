#include "InvalidRequest.h"
#include "../Response.h"

InvalidRequest::InvalidRequest() : Request() {
}

string InvalidRequest::getHelpMsg() {
    return "";
}

Response *InvalidRequest::execute() {
    // create new invalid request response and return it
    auto *response = new Response(INVALID_REQUEST, "invalid request.");

    return response;
};
