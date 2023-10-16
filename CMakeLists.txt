cmake_minimum_required(VERSION 3.22)
project(LexicalAnalyzer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LexicalAnalyzer
        Assignment1.cpp
        LexicalAnalyzer.cpp
        LexicalAnalyzer.h
        Token.cpp
        Token.h
        TokenCodes.h)
