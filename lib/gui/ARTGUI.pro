#-------------------------------------------------
#
# Project created by QtCreator 2016-09-23T19:08:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ARTGUI
TEMPLATE = app
INCLUDEPATH += \
        include


SOURCES += lib/MainWindow/main.cpp\
    lib/MainWindow/MainWindow.cpp \
    lib/AboutArt/AboutArt.cpp \
    lib/utils/StringUtil.cpp \
    lib/WorkSpace/WorkSpace.cpp \
    lib/OpenApk/OpenApk.cpp \
    lib/utils/ProjectInfo.cpp \
    lib/utils/Configuration.cpp \
    lib/WorkSpace/TabWidget.cpp \
    lib/WorkSpace/TabBar.cpp \
    lib/ProjectTab/ProjectTab.cpp \
    lib/ProjectTab/ProjectTab.cpp \
    lib/EditorTab/EditorTab.cpp \
    lib/BookMark/BookMark.cpp \
    lib/RunDevice/RunDevice.cpp \
    lib/Config/Config.cpp \
    lib/Config/FileEditor.cpp \
    lib/Find/FindDialog.cpp \
    lib/Find/FindWidget.cpp \
    lib/Find/FindConfig.cpp \
    lib/Find/FindResult.cpp


HEADERS  += \
    include/MainWindow/MainWindow.h \
    include/AboutArt/AboutArt.h \
    include/utils/StringUtil.h \
    lib/WorkSpace/WorkSpace.h \
    lib/OpenApk/OpenApk.h \
    include/utils/ProjectInfo.h \
    include/utils/Configuration.h \
    include/WorkSpace/WorkSpace.h \
    lib/WorkSpace/TabWidget.h \
    lib/WorkSpace/TabBar.h \
    lib/ProjectTab/ProjectTab.h \
    include/ProjectTab/ProjectTab.h \
    lib/ProjectTab/ProjectTab.h \
    include/EditorTab/EditorTab.h \
    lib/BookMark/BookMark.h \
    include/BookMark/BookMark.h \
    lib/RunDevice/RunDevice.h \
    lib/Config/Config.h \
    lib/Config/FileEditor.h \
    lib/Find/FindDialog.h \
    lib/Find/FindWidget.h \
    lib/Find/FindConfig.h \
    lib/Find/FindResult.h

FORMS    += \
    lib/MainWindow/MainWindow.ui \
    lib/AboutArt/AboutArt.ui \
    lib/WorkSpace/WorkSpace.ui \
    lib/OpenApk/OpenApk.ui \
    lib/ProjectTab/ProjectTab.ui \
    lib/ProjectTab/projecttab.ui \
    lib/ProjectTab/ProjectTab.ui \
    include/EditorTab/EditorTab.ui \
    lib/EditorTab/EditorTab.ui \
    lib/BookMark/BookMark.ui \
    lib/RunDevice/RunDevice.ui \
    lib/Config/Config.ui \
    lib/Config/FileEditor.ui \
    lib/Find/FindDialog.ui \
    lib/Find/FindWidget.ui \
    lib/Find/FindConfig.ui \
    lib/Find/FindResult.ui

RESOURCES += \
    ART.qrc \
    lib/Res/ART.qrc
