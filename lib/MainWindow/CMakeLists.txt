SET(TARGET_NAME MainWindow)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

FILE(GLOB_RECURSE GUI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c* ${CMAKE_CURRENT_SOURCE_DIR}/*.h* ${ART_INCLUDE_DIR}/${TARGET_NAME}/*.h)


add_executable(${TARGET_NAME} ${GUI_SRCS} ../../ART.qrc)
target_link_libraries(${TARGET_NAME} AboutArt OpenApk RunDevice
        ProjectTab EditorTab Find Config Debugger)
qt5_use_modules(${TARGET_NAME} Widgets)