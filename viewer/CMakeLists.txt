file(GLOB_RECURSE VIEWER_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_executable(viewer ${VIEWER_SOURCES})

target_link_libraries(viewer PRIVATE kinematics_core)