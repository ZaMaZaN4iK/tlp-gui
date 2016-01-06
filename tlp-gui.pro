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
    WindowSettings.cpp \
    SystemTray.cpp \
    HelpBrowser.cpp \
    Backend.cpp \
    Parser.cpp \
    MainWindow.cpp \
    TableModel.cpp \
    Property.cpp \
    QComboBoxItemDelegate.cpp \
    Tabel.cpp

HEADERS  += \
    WindowSettings.h \
    SystemTray.h \
    HelpBrowser.h \
    Backend.h \
    Parser.h \
    MainWindow.h \
    TableModel.h \
    Property.h \
    QComboBoxItemDelegate.h \
    Tabel.h

FORMS    +=

DISTFILES +=

RESOURCES += \
    images.qrc

