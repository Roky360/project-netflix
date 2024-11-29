#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <string>
#include <vector>

using namespace std;

class TestUtils {
public:
    /**
     * A helper function that reads the db file contents to compare output in the tests.
     *
     * @return A string representation of the database file.
     */
    static string readDbFile();

    /**
     * A helper function that returns a string representation of an int array.
     *
     * @param arr
     * @return
     */
    static string intArrToString(const vector<int> &arr);
};

#endif //TESTUTILS_H
