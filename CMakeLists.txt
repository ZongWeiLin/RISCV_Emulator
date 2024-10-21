cmake_minimum_required(VERSION 2.8)

project(ALISS)

find_package(GTest REQUIRED)
set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB TEST_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/test/*.cpp)

# set(SOURCE_FILES src/main.cpp)
# set(TEST_FILES src/test_main.cpp)

add_executable(ALISS ${SOURCE_FILES})
add_executable(ALISS_TEST ${TEST_FILES} ${CMAKE_CURRENT_SOURCE_DIR}/src/ALISS.cpp)
target_link_libraries(ALISS_TEST gtest GTest::GTest GTest::Main)

add_test(MAIN_TEST ALISS_TEST) 