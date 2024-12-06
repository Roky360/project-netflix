#ifndef PROJECT_NETFLIX_CLIENTCONTEXT_H
#define PROJECT_NETFLIX_CLIENTCONTEXT_H

#include <map>
#include <string>
#include <variant>

using namespace std;

class ClientContext {
public:

    /**
     * return the val of the key in the map
     * if the key not found - throw invalid_argument exception
     * @param key the key in the map
     * @return the val of the key
     */
    string getField(const string& key) const;

    /**
     * get key and val and enter them to the map
     * @param key the key
     * @param value the map
     */
    void setField(const string& key, const string& value);

    /**
     * @param key the key
     * @return true is the key exist, false otherwise
     */
    bool hasField(const string& key) const;

    /**
     * add the key and the val to the map
     * note: if the key already exist - only change his value!
     * @param key the key
     * @param val the key value
     */
    void addField(const string& key, const string& val);

private:
    map<string, string> args;

};

#endif //PROJECT_NETFLIX_CLIENTCONTEXT_H
