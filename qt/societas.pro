#-------------------------------------------------
#
# Main Project
# by Central Services
#
# Current version: 0.1.0
# Not Public Release
#-------------------------------------------------

VERSION = 0.1.0
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Societas
TEMPLATE = app

FORMS    += gui.ui
INCLUDEPATH += ../include \
               ../src
HEADERS += \
     ../include/gui.h

SOURCES += \
    ../src/gui.cpp \
    ../src/main.cpp
