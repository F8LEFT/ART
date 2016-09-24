cmake_minimum_required(VERSION 3.5)
project(ARTGUI)

set(CMAKE_PREFIX_PATH /home/f8left/CodeProgram/QT/5.7/gcc_64)

set(CMAKE_C_COMPILER "g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
#查找Qt的库
find_package(Qt5Widgets)
find_package(Qt5Xml)

include_directories(include)

aux_source_directory(lib/MainWindow MainWindow_SRC)

set(SOURCE_FILES main.cpp ${MainWindow_SRC} include/MainWindow/MainWindow.h)

add_executable(ARTGUI ${SOURCE_FILES})

target_link_libraries(ARTGUI Qt5::Widgets Qt5::Xml)
