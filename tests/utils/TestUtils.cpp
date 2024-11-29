#include "TestUtils.h"
#include "../../src/database/FilesDatabase.h"
#include <fstream>
#include <sstream>

using namespace db;

string TestUtils::readDbFile() {
    ifstream f(FilesDatabase::DB_FILE_PATH);
    stringstream buff;
    string line;
    if (!f.good())
        return "";
    while (getline(f, line)) {
        buff << line << '\n';
    }
    string contents = buff.str();
    return contents.substr(0, contents.length() - 1);
}

string TestUtils::intArrToString(const vector<int> &arr) {
    string s = "[";
    for (auto elem: arr) {
        s += to_string(elem) + " ";
    }
    if (s.length() == 1)
        s += "]";
    else
        s = s.substr(0, s.length() - 1) + "]";
    return s;
}
