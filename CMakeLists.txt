cmake_minimum_required(VERSION 3.10)
project(CantorovoSetTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ГЛАВНОЕ: ФЛАГИ ПОКРЫТИЯ для DEBUG сборки
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Building with coverage flags")
    # Компиляция с покрытием
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage -g -O0")
    # Линковка с покрытием
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fprofile-arcs -lgcov")
endif()

# Пути к исходникам проекта и Google Test
set(SRC_FILES CantorovoSet.cpp)
set(TEST_FILES tests.cpp)

# Добавляем Google Test
add_subdirectory(googletest)

# Создаем исполняемый файл для тестов
add_executable(tests ${SRC_FILES} ${TEST_FILES})

# Линкуем с gtest и gtest_main
target_link_libraries(tests gtest gtest_main pthread)

# Для покрытия - линковка gcov (только в Debug)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(tests gcov)
endif()

# Делаем тесты доступными через ctest
enable_testing()
add_test(NAME AllTests COMMAND tests)