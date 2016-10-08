cmake_minimum_required(VERSION 3.5)
project(SmaliParse)

set(SRC_FILE Lexer.cpp Parser.cpp)

ADD_EXECUTABLE(SmaliParse_Test main.cpp ${SRC_FILE})
ADD_LIBRARY(SmaliParse ${SRC_FILE})
target_include_directories(SmaliParse PUBLIC .)