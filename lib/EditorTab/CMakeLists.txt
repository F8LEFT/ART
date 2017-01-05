SET(TARGET_NAME EditorTab)

FILE(GLOB_RECURSE GUI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c* ${CMAKE_CURRENT_SOURCE_DIR}/*.h* ${ART_INCLUDE_DIR}/${TARGET_NAME}/*.h)


add_library(${TARGET_NAME} STATIC ${GUI_SRCS})
target_link_libraries(${TARGET_NAME} utils BookMark BreakPoint
        Qt5::Widgets KF5SyntaxHighlighting SmaliParse)
