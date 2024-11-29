# Tests CMake configuration

# Include gtest
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.tar.gz
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test executable
file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*.h" "*.cpp")
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp") # remove the main so the tests' main will be executed
add_executable(unit_tests ${SOURCES} ${TEST_SOURCES}
        utils/TestUtils.cpp
        utils/TestUtils.h)

# Link GTest and pthread for tests
target_link_libraries(unit_tests gtest gtest_main pthread)

# Add the test to CTest
add_test(NAME unit_tests COMMAND unit_tests)
include(GoogleTest)
gtest_discover_tests(unit_tests)
