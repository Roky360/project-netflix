#include "Utils.h"

using namespace std;

namespace utils {
    vector<string> Utils::split(const string& s, const string& delimiter) {
        string str = string(s);
        vector<string> tokens;
        size_t pos = 0;
        string token;
        while ((pos = str.find(delimiter)) != std::string::npos) {
            token = str.substr(0, pos);
            tokens.push_back(token);
            str.erase(0, pos + delimiter.length());
        }
        tokens.push_back(str);

        return tokens;
    }
} // utils