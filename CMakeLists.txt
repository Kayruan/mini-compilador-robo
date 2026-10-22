cmake_minimum_required(VERSION 3.10)

project(MiniCompilador CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aula6
    src/aula6.cpp
    src/lexer.cpp
    src/parser.cpp
    src/semantic.cpp
    src/symtable.cpp
)

target_include_directories(aula6 PRIVATE include)
