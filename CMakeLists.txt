# Set cmake version
#set(MIN_VER 3.27.8)
#option(CMAKE_VER "Target cmake version" ${MIN_VER})
#if (CMAKE_VER VERSION_LESS ${MIN_VER})
#    set(CMAKE_VER ${MIN_VER})
#endif ()
#cmake_minimum_required(VERSION ${CMAKE_VER})
cmake_minimum_required(VERSION 3.27.8)

project(project_netflix)
set(CMAKE_CXX_STANDARD 14)

# Main executable
file(GLOB SOURCES "src/*.cpp")
add_executable(project_netflix ${SOURCES})
#add_executable(project_netflix src/main.cpp
#        src/request/AddMovieRequest.cpp
#        src/request/AddMovieRequest.h
#        src/request/RecommendMovieRequest.cpp
#        src/request/RecommendMovieRequest.h
#        src/request/HelpRequest.cpp
#        src/request/InvalidRequest.cpp
#        src/request/Request.cpp
#        src/request_Provider/CliRequestProvider.cpp
#        src/database/Database.h
#        src/database/FilesDatabase.cpp
#        src/database/FilesDatabase.h
#        src/utils/Utils.cpp
#        src/utils/Utils.h)

# If tests are enabled, include CMake for tests
option(BUILD_TESTS "Build gtest tests" OFF)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()

## Add Google Test
#include(FetchContent)
#
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
#)
#
## Ensure GTest is built
#FetchContent_MakeAvailable(googletest)
#
## Enable testing
#enable_testing()
#
## Add test executable
#add_executable(MyTests tests/my_tests.cpp
#        src/Request/AddMovieRequest.cpp
#        src/Request/AddMovieRequest.h
#        src/database/Database.h
#        src/database/FilesDatabase.cpp
#        src/database/FilesDatabase.h
#        src/utils/Utils.cpp
#        src/utils/Utils.h)
#
## Link GTest and pthread for tests
#target_link_libraries(MyTests gtest gtest_main pthread)
#
## Add the test to CTest
#add_test(NAME MyTests COMMAND MyTests)
#
## Optionally set up separate build modes for running the project and tests
#set_property(TARGET MyTests PROPERTY EXCLUDE_FROM_ALL TRUE)
