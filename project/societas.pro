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

TARGET = societas
TEMPLATE = app

INCLUDEPATH +=../include

include($${SOLUTION_DIR}../societas.pri)

FORMS    += gui.ui
