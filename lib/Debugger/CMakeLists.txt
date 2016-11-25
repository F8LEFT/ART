SET(TARGET_NAME Debugger)

FILE(GLOB_RECURSE GUI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c* ${CMAKE_CURRENT_SOURCE_DIR}/*.h* ${GUI_INCLUDE_DIR}/${TARGET_NAME}/*.h)
aux_source_directory(Jdwp JDWPSRC)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
source_group_by_dir(GUI_SRCS)

add_library(${TARGET_NAME} STATIC ${GUI_SRCS} ${JDWPSRC})
target_link_libraries(${TARGET_NAME} utils)
qt5_use_modules(${TARGET_NAME} Widgets WebSockets)