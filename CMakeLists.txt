cmake_minimum_required(VERSION 3.27.8)
project(project_netflix)

set(CMAKE_CXX_STANDARD 14)

# Main executable
add_executable(project_netflix src/main.cpp
        src/database/Database.h
        src/database/FilesDatabase.cpp
        src/database/FilesDatabase.h
        src/utils/Utils.cpp
        src/utils/Utils.h
        src/Services/MoviesService.cpp
        src/Services/MoviesService.h)

# Add Google Test
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
)

# Ensure GTest is built
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Add test executable
add_executable(MyTests tests/files_db_tests.cpp
        src/database/Database.h
        src/database/FilesDatabase.cpp
        src/database/FilesDatabase.h
        src/utils/Utils.cpp
        src/utils/Utils.h)

# Link GTest and pthread for tests
target_link_libraries(MyTests gtest gtest_main pthread)

# Add the test to CTest
add_test(NAME MyTests COMMAND MyTests)

# Optionally set up separate build modes for running the project and tests
set_property(TARGET MyTests PROPERTY EXCLUDE_FROM_ALL TRUE)
