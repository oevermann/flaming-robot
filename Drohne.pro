#-------------------------------------------------
#
# Project created by QtCreator 2012-11-22T22:24:19
#
#-------------------------------------------------

QT       += core gui network

TARGET = Drohne
TEMPLATE = app


SOURCES += main.cpp\
        steuerung.cpp \
    dialog.cpp \
    daten.cpp \
    server.cpp \
    serverthread.cpp

HEADERS  += steuerung.h \
    dialog.h \
    daten.h \
    server.h \
    serverthread.h

FORMS    += steuerung.ui \
    dialog.ui
