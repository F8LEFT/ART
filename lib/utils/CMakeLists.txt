SET(TARGET_NAME utils)

FILE(GLOB_RECURSE GUI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c* ${CMAKE_CURRENT_SOURCE_DIR}/*.h* ${ART_INCLUDE_DIR}/${TARGET_NAME}/*.h*)

add_library(ART_utils STATIC ${GUI_SRCS})
target_link_libraries(ART_utils)
