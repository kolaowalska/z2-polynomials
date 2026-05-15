cmake_minimum_required(VERSION 3.14)
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

# ---------------------------------------------------------------------------
# Tests
# ---------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(z2_tests tests/test.cpp)
target_link_libraries(z2_tests PRIVATE z2_core Catch2::Catch2WithMain)

enable_testing()
include(CTest)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(z2_tests)
