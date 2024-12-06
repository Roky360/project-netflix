#include "ClientContext.h"
#include <stdexcept>

string ClientContext::getField(const string& key) const {
    // find the key in the map
    auto field = this->args.find(key);

    // if the key exist return his val
    if (field != this->args.end()) {
        return field->second;
    }

    // else throw exception
    throw invalid_argument("Invalid key " + key);
}

void ClientContext::setField(const string &key, const string &value) {
    // set the key val to value
    this->args[key] = value;
}

bool ClientContext::hasField(const string &key) const {
    // return if the key is in the map
    return this->args.find(key) != this->args.end();
}

void ClientContext::addField(const string &key, const string &val) {
    // check if the key is already exist, if it does - only change his field.
    if (this->hasField(key)) {
        this->setField(key, val);
    }
    // if the key is not exist enter in to the map
    else {
        this->args[key] = val;
    }
}