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
    lib/MainWindow/MainWindow.cpp


HEADERS  += \
    include/MainWindow/MainWindow.h

FORMS    += \
    lib/MainWindow/MainWindow.ui
