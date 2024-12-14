#include "Response.h"

#include <utility>

const map<Status, string> Response::statusMap = {
    {OK_200, "200 OK"},
    {CREATED_201, "201 Created"},
    {NO_CONTENT_204, "204 No Content"},
    {BAD_REQUEST_400, "400 Bad Request"},
    {NOT_FOUND_404, "404 Not Found"}
};


Response::Response(const Status s, ClientContext *cl, string payload) : status(s), payload(std::move(payload)),
                                                                        context(cl) {
}

string Response::toRawData() const {
    // get the string for the status from the map
    string str = statusMap.find(this->status)->second;

    // if the response payload is not empty add it to the string
    if (!this->payload.empty()) {
        str += "\n\n" + this->payload;
    }
    str += "\n";

    // return the string
    return str;
}
