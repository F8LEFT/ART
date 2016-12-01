SET(TARGET_NAME HighLighter)

FILE(GLOB_RECURSE GUI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c* ${CMAKE_CURRENT_SOURCE_DIR}/*.h* ${ART_INCLUDE_DIR}/${TARGET_NAME}/*.h)
aux_source_directory(KateHighlight KateHL)

add_library(${TARGET_NAME} STATIC ${GUI_SRCS} ${KateHL})
target_link_libraries(${TARGET_NAME} utils BookMark SmaliParse)
qt5_use_modules(${TARGET_NAME} Widgets)
