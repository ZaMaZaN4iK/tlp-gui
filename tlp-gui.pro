#-------------------------------------------------
#
# Project created by QtCreator 2015-12-30T20:04:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tlp-gui
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    WindowSettings.cpp \
    SystemTray.cpp \
    HelpBrowser.cpp \
    Backend.cpp \
    Parser.cpp

HEADERS  += mainwindow.h \
    WindowSettings.h \
    SystemTray.h \
    HelpBrowser.h \
    Backend.h \
    Parser.h

FORMS    +=

DISTFILES +=

RESOURCES += \
    images.qrc

