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

mac:{
#XMPP and Crypto dependencies
LIBS += -L/usr/local/lib  -lresolv -lgloox  -lcrypto -lssl -lz -lidn
#MONGOOSE webserver dependencies
LIBS += -L/usr/local/lib -lmongoose

}
TARGET = societas
TEMPLATE = app

INCLUDEPATH +=../include

include($${SOLUTION_DIR}../societas.pri)


