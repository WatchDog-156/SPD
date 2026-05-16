cmake_minimum_required(VERSION 3.10)

project(maszyny_rownolegle VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(maszyny_rownolegle src/main.cpp
                                  src/zadanie.cpp
                                  src/permutacja.cpp
                                  src/problem.cpp
)

target_include_directories(maszyny_rownolegle PRIVATE inc)