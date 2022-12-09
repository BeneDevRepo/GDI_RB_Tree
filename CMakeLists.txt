cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 14)

file(GLOB_RECURSE files "src/*.cpp")
add_executable(Aufgaben_2 ${files})
target_include_directories(Aufgaben_2 PUBLIC "src")
