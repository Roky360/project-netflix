#ifndef PROJECT_NETFLIX_UTILS_H
#define PROJECT_NETFLIX_UTILS_H

#include <string>
#include <vector>

using namespace std;

namespace utils {
    class Utils {
    public:
        /**
         * Splits a string by a given delimiter.
         *
         * @param s
         * @param delimiter
         * @return An array containing all the elements.
         */
        static vector<string> split(const string& s, const string& delimiter);
    };

} // utils

#endif //PROJECT_NETFLIX_UTILS_H
