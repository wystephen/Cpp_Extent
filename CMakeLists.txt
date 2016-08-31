cmake_minimum_required(VERSION 3.5)

project(Cpp_Extent)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


add_executable(test_main Cpp_Extent/test_main.cpp Cpp_Extent/CSVReader.h Cpp_Extent/Matrix.h)



