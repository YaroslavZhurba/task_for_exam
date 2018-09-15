cmake_minimum_required(VERSION 3.10)
project(task_for_exam)

set(CMAKE_CXX_STANDARD 14)

add_executable(task_for_exam
        #main.cpp
        vector.h
        base_vector.h
        doctest/doctest.h
        vector_tests.cpp)