cmake_minimum_required(VERSION 3.14)
project(banking)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-isystem")

include_directories(${PROJECT_SOURCE_DIR}/banking)

add_subdirectory(banking)

option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)

    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip 
    )

    set(BUILD_GMOCK ON CACHE INTERNAL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    file(GLOB TEST_SOURCES tests/*.cpp)

    add_executable(runTests ${TEST_SOURCES})

    target_link_libraries(runTests PRIVATE banking gmock_main)

    enable_testing()
    add_test(NAME runTests COMMAND runTests)
endif()

option(COVERAGE "Enable coverage reporting" OFF)

if(COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()
