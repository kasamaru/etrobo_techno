cmake_minimum_required(VERSION 3.14)
project(etrobotest)
 
set(CMAKE_BUILD_TYPE Debug)
 
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
include(FetchContent)
FetchContent_Declare(
 googletest
 URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
 
enable_testing()
 
# this include path change your local enviroment
include_directories($ENV{HOME}/etrobo/workspace/etrobo2023/app)
 
#file: test scope file
file(GLOB_RECURSE TEST_SOURCES "app/*.cpp")
add_executable(EtRoboTest ${TEST_SOURCES})
 
target_link_libraries(
 EtRoboTest
 GTest::gtest_main
)
 
include(GoogleTest)
gtest_discover_tests(EtRoboTest)