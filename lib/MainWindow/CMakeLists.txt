SET(TARGET_NAME MainWindow)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GUI_PROJDIR}/bin)

FILE(GLOB_RECURSE GUI_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.c* ${CMAKE_CURRENT_SOURCE_DIR}/*.h* ${GUI_INCLUDE_DIR}/${TARGET_NAME}/*.h)

source_group_by_dir(GUI_SRCS)

add_executable(${TARGET_NAME} ${GUI_SRCS} ../../ART.qrc)
target_link_libraries(${TARGET_NAME} AboutArt WorkSpace OpenApk RunDevice
        Config)
qt5_use_modules(${TARGET_NAME} Widgets)