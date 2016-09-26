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
    lib/WorkSpace/TabBar.cpp


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
    lib/WorkSpace/TabBar.h

FORMS    += \
    lib/MainWindow/MainWindow.ui \
    lib/AboutArt/AboutArt.ui \
    lib/WorkSpace/WorkSpace.ui \
    lib/OpenApk/OpenApk.ui
