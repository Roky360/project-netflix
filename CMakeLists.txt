# Set cmake version
set(MIN_VER 3.25.1)
option(CMAKE_VER "Target cmake version" ${MIN_VER})
if (CMAKE_VER VERSION_LESS ${MIN_VER})
    set(CMAKE_VER ${MIN_VER})
endif ()
cmake_minimum_required(VERSION ${CMAKE_VER})

project(project_netflix)
set(CMAKE_CXX_STANDARD 14)

# Add executable with all source files under `src`
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")
add_executable(project_netflix ${SOURCES})

# If tests are enabled, include cmake file for tests
option(BUILD_TESTS "Build gtest tests" OFF)
if ("${BUILD_TESTS}" STREQUAL "ON")
    add_subdirectory(tests)
endif ()
