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
    lib/WorkSpace/WorkSpace.cpp


HEADERS  += \
    include/MainWindow/MainWindow.h \
    include/AboutArt/AboutArt.h \
    include/utils/StringUtil.h \
    lib/WorkSpace/WorkSpace.h

FORMS    += \
    lib/MainWindow/MainWindow.ui \
    lib/AboutArt/AboutArt.ui \
    lib/WorkSpace/WorkSpace.ui
