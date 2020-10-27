cmake_minimum_required(VERSION 3.10)

project(Homework2)

add_executable(main main.cc)

target_link_libraries(main PUBLIC ComputeArithmetic)
target_link_libraries(main PUBLIC ComputePi)
# target_link_libraries(main PUBLIC Series)

add_library(ComputeArithmetic ComputeArithmetic.cc)
add_library(ComputePi ComputePi.cc)

#add_library(Series Series.cc)

