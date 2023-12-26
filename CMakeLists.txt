cmake_minimum_required(VERSION 3.0)
project(lox)

add_executable(
    lox 
    src/main.cpp
    src/scanner.cpp
    src/token.cpp
    src/error_logger.cpp
)
