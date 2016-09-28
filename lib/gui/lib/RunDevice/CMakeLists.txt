SET(TARGET_NAME RunDevice)

FILE(GLOB_RECURSE GUI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c* ${CMAKE_CURRENT_SOURCE_DIR}/*.h* ${GUI_INCLUDE_DIR}/${TARGET_NAME}/*.h)

source_group_by_dir(GUI_SRCS)

add_library(${TARGET_NAME} STATIC ${GUI_SRCS})
target_link_libraries(${TARGET_NAME} utils)
qt5_use_modules(${TARGET_NAME} Widgets)