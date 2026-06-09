cmake_minimum_required(VERSION 4.1)
project(kinematics)

set(CMAKE_CXX_STANDARD 20)
find_package(Eigen3 REQUIRED NO_MODULE)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_library(kinematics_core STATIC ${SOURCES})

target_link_libraries(kinematics_core PUBLIC Eigen3::Eigen)

target_include_directories(kinematics_core PUBLIC src)

#add_executable(kinematics src/main.cpp)
#target_link_libraries(kinematics PRIVATE kinematics_core)

# Testing
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "tests/*.cpp" "tests/*.hpp")

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests PRIVATE
        GTest::gtest_main
        kinematics_core
)

include(GoogleTest)
gtest_discover_tests(run_tests)