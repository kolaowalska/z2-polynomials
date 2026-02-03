cmake_minimum_required(VERSION 4.1)
project(z2_polynomials)

set(CMAKE_CXX_STANDARD 20)

add_executable(z2_polynomials
        main.cpp
        Polynomial.h
        Polynomial.cpp)
