cmake_minimum_required(VERSION 3.31)
project(kinematics)

set(CMAKE_CXX_STANDARD 20)

# clang shit
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

option(ENABLE_VIEWER "Enable kinematics viewer" ON)

find_package(Eigen3 REQUIRED NO_MODULE)
set(SOURCE_ROOT "${CMAKE_SOURCE_DIR}")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_library(kinematics_core STATIC ${SOURCES})

target_link_libraries(kinematics_core PUBLIC Eigen3::Eigen)

target_include_directories(kinematics_core PUBLIC src)

if(ENABLE_VIEWER)
    message(STATUS "Building viewer is ENABLED.")
    add_subdirectory(viewer)
else()
    message(STATUS "Building viewer is DISABLED.")
endif()

# Testing
enable_testing()
add_subdirectory(tests)