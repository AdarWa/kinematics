cmake_minimum_required(VERSION 3.31)
project(kinematics)

set(CMAKE_CXX_STANDARD 20)
find_package(Eigen3 REQUIRED NO_MODULE)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_library(kinematics_core STATIC ${SOURCES})

target_link_libraries(kinematics_core PUBLIC Eigen3::Eigen)

target_include_directories(kinematics_core PUBLIC src)

add_subdirectory(viewer)

# Testing
enable_testing()
add_subdirectory(tests)