cmake_minimum_required(VERSION 3.11.0)

project(numericxx_test
  VERSION 0.1.0
  LANGUAGES C CXX)

add_executable(test_main
  main.cpp)

target_include_directories(test_main PRIVATE ../include/)