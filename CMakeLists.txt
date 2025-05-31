cmake_minimum_required(VERSION 3.14)
project(banking)

# Используем C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Отключаем системные инклюды как "system includes" (чтобы не мешали FetchContent)
set(CMAKE_INCLUDE_SYSTEM_FLAG_CXX "-isystem")

# Добавляем include директорию проекта
include_directories(${PROJECT_SOURCE_DIR}/banking)

# Включаем подпроект banking
add_subdirectory(banking)

# Опция: собирать ли тесты
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)

    # Подключение Google Test через FetchContent
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip 
    )

    set(BUILD_GMOCK ON CACHE INTERNAL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    # Тестовые файлы
    file(GLOB TEST_SOURCES tests/*.cpp)

    # Создаем исполняемый файл для тестов
    add_executable(runTests ${TEST_SOURCES})

    # Линкуем с библиотеками
    target_link_libraries(runTests PRIVATE banking gmock_main)

    # Включаем тестирование
    enable_testing()
    add_test(NAME runTests COMMAND runTests)
endif()

# Опция: сборка с покрытием кода
option(COVERAGE "Enable coverage reporting" OFF)

if(COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()
