cmake_minimum_required(VERSION 3.16)
project(sequence_alignment LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(alignment
    src/main.cpp
    src/alignment/NeedlemanWunsch.cpp
    src/alignment/Hirschberg.cpp
    src/utils/Timer.cpp
)