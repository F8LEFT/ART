SET(TARGET_NAME Config)

FILE(GLOB_RECURSE GUI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c* ${CMAKE_CURRENT_SOURCE_DIR}/*.h* ${ART_INCLUDE_DIR}/${TARGET_NAME}/*.h)


add_library(${TARGET_NAME} STATIC ${GUI_SRCS})
target_link_libraries(${TARGET_NAME} utils EditorTab KF5SyntaxHighlighting Qt5::Widgets )
