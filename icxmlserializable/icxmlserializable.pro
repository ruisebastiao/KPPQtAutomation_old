#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T13:41:44
#
#-------------------------------------------------

QT       -= gui
QT       += core xml

TARGET = icxmlserializable
TEMPLATE = lib

DEFINES += ICXMLSERIALIZABLE_LIBRARY

SOURCES += icxmlserializable.cpp

HEADERS += icxmlserializable.h\
        icxmlserializable_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}


QMAKE_CFLAGS_RELEASE += -Zi
QMAKE_CXXFLAGS_RELEASE += -Zi
QMAKE_LFLAGS_RELEASE += /DEBUG /OPT:REF

! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!")
}
