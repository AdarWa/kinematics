cmake_minimum_required(VERSION 4.1)
project(kinematics)

set(CMAKE_CXX_STANDARD 20)
find_package(Eigen3 REQUIRED NO_MODULE)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.hpp")

add_executable(kinematics ${SOURCES})
target_link_libraries(kinematics Eigen3::Eigen)
