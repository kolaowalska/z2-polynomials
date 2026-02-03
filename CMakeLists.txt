cmake_minimum_required(VERSION 4.1)
project(z2_polynomials)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(z2_core
        src/Polynomial.cpp
        src/Z2.cpp
)

target_include_directories(z2_core PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
)

add_executable(z2_app src/main.cpp)
target_link_libraries(z2_app PRIVATE z2_core)

enable_testing()

