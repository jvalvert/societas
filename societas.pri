INCLUDEPATH += ../include
HEADERS += \
    $$PWD/include/PresentationLayer.h \
    $$PWD/include/ApplicationLayer.h \
    $$PWD/include/BusinessLayer.h \
    $$PWD/include/DataAccessLayer/xmppClient.h \
    $$PWD/include/BusinessLayer.h \
    $$PWD/include/DataAccessLayer.h \
    $$PWD/include/DataAccessLayer/webSocketClient.h
SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/PresentationLayer.cpp \
    $$PWD/src/ApplicationLayer.cpp \
    $$PWD/src/BusinessLayer.cpp \
    $$PWD/src/DataAccessLayer/xmppClient.cpp \
    $$PWD/src/DataAccessLayer.cpp \
    $$PWD/src/DataAccessLayer/webSocketClient.cpp



FORMS    +=  $$PWD/src/forms/MainWindow.ui

