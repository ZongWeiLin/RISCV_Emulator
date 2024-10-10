cmake_minimum_required(VERSION 2.8)

project(ALISS)

find_package(GTest REQUIRED)
set(CMAKE_CXX_STANDARD 11)

##Set Project root path
set(Proj /home/wei/git_repos/RISCV_Emulator)

set(SOURCE_FILES ${Proj}/src/main.cpp)

set(TEST_FILES ${Proj}/src/test_main.cpp)

add_executable(ALISS ${SOURCE_FILES})
add_executable(ALISS_TEST ${TEST_FILES})
target_link_libraries(ALISS_TEST gtest GTest::GTest GTest::Main)

add_test(MAIN_TEST ALISS_TEST) 