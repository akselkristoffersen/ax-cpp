include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.6.0
)
FetchContent_MakeAvailable(Catch2)

file(GLOB TEST_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(test_${PROJECT_NAME} ${TEST_SOURCES})

target_link_libraries(test_${PROJECT_NAME}
    PRIVATE
        Catch2::Catch2WithMain
        ${PROJECT_NAME}::${PROJECT_NAME}
)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(test_${PROJECT_NAME})