#-------------------------------------------------
#
# Project created by QtCreator 2016-02-21T21:53:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network

TARGET = ae
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    3rd/pugixml/pugixml.cpp

HEADERS  += mainwindow.h \
    global.h \
    3rd/pugixml/pugiconfig.hpp \
    3rd/pugixml/pugixml.hpp

FORMS    += mainwindow.ui

win32: {
    QMAKE_CXXFLAGS += /D_USING_V120_SDK71_
    QMAKE_LFLAGS_CONSOLE += /SUBSYSTEM:CONSOLE,5.01
    QMAKE_LFLAGS_WINDOWS += /SUBSYSTEM:WINDOWS,5.01
}

win32: LIBS += -L$$PWD/bin
win32: INCLUDEPATH += $$PWD/3rd/pugixml

RESOURCES += \
    res.qrc

DISTFILES += \
    res/res.rc

RC_FILE = res/res.rc
