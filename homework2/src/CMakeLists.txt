cmake_minimum_required(VERSION 3.10)

project(Homework2)

add_executable(main main.cc)

target_link_libraries(main PUBLIC ComputeArithmetic)

add_library(ComputeArithmetic ComputeArithmetic.cc)

