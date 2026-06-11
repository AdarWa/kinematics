include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "*.cpp" "*.hpp")

add_executable(run_tests ${TEST_SOURCES})

target_link_libraries(run_tests PRIVATE
        GTest::gtest_main
        kinematics_core
)

include(GoogleTest)
gtest_discover_tests(run_tests)