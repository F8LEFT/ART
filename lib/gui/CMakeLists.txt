cmake_minimum_required(VERSION 3.5)
project(ARTGUI)

SET(CMAKE_PREFIX_PATH /home/f8left/CodeProgram/QT/5.7/gcc_64)

SET(CMAKE_C_COMPILER "g++")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Werror")

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_SUPPRESS_REGENERATION 1)
SET(CMAKE_USE_RELATIVE_PATHS ON)
SET(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)

SET(PROJDIR ${CMAKE_CURRENT_SOURCE_DIR})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

SET(CMAKE_INSTALL_PREFIX ${PROJDIR}/bin)

SET(GUI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

INCLUDE_DIRECTORIES(${GUI_INCLUDE_DIR})
FIND_PACKAGE(Qt5Widgets REQUIRED)

macro(source_group_by_dir source_files)
    if(MSVC)
        set(sgbd_cur_dir ${CMAKE_CURRENT_SOURCE_DIR})
        foreach(sgbd_file ${${source_files}})
            string(REGEX REPLACE ${sgbd_cur_dir}//(.*/) //1 sgbd_fpath ${sgbd_file})
            string(REGEX REPLACE "/(.*/)/.*" //1 sgbd_group_name ${sgbd_fpath})
            string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
            string(REPLACE "/" "//" sgbd_group_name ${sgbd_group_name})
            if(sgbd_nogroup)
                set(sgbd_group_name "//")
            endif(sgbd_nogroup)
            source_group(${sgbd_group_name} FILES ${sgbd_file})
        endforeach(sgbd_file)
    endif(MSVC)
endmacro(source_group_by_dir)

ADD_SUBDIRECTORY(lib)

SET(LIBS ${LIBRARY_OUTPUT_PATH})
LINK_DIRECTORIES(${LIBS})

