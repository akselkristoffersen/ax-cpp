include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/1204d634444b0ba6da53201a8b6caf2a502d883c.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(TEST_EXEC_NAME test_${PROJECT_NAME})

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(${TEST_EXEC_NAME} ${TEST_SOURCES})

target_link_libraries(${TEST_EXEC_NAME}
    PRIVATE
        GTest::gtest_main
        ${PROJECT_NAME}::${PROJECT_NAME}
)

include(GoogleTest)
gtest_discover_tests(${TEST_EXEC_NAME})