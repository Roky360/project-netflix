#include <iostream>
#include "database/FilesDatabase.h"
#include "utils/Utils.h"

using namespace std;
using namespace db;
using namespace utils;

int main() {
    auto *db = new FilesDatabase();

    db->addMovieToUser("104", "1001");
    db->addMovieToUser("104", "1002");
    db->addMovieToUser("102", "1001");
    db->addMovieToUser("105", "1008");
    db->addMovieToUser("102", "1009");
//    db->addMovieToUser("104", "1001");

    return 0;
}

/*
104 1001 1002
102 1001
105 1008

104 1001 1002
10102 1001 1009
8

 * */
