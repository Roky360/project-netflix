#include "InvalidRequest.h"
#include "Response.h"
#include <iostream>

InvalidRequest::InvalidRequest() : Request() {}

Response* InvalidRequest::execute() {
    // create new invalid request response and return it
    Response* response = new Response(INVALID_REQUEST, "invalid request.");

    return response;
};