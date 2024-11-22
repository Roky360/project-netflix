#include "InvalidRequest.h"
#include "Response.h"
#include <iostream>

Response* InvalidRequest::execute() {
    Response* response = new Response(INVALID_REQUEST, "invalid request.");
    //cout << "invalid request" << endl; // for debug
    return response;
};