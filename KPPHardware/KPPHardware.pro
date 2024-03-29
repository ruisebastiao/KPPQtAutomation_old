#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T13:59:23
#
#-------------------------------------------------

QT       += core xml gui widgets

TARGET = KPPHardware
TEMPLATE = lib

DEFINES += KPPHARDWARE_LIBRARY
QMAKE_CXXFLAGS += /DNOMINMAX
SOURCES += \
    camerainfo.cpp \
    idscamera.cpp \
    idscamerainfo.cpp \
    idseventsthandler.cpp \
    kpphardware.cpp

HEADERS +=\
        kpphardware_global.h \
    camerainfo.h \
    idscamera.h \
    idscamerainfo.h \
    idseventsthandler.h \
    ui_idscameraconfig.h \
    kpphardware.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}




unix|win32: LIBS += -L$$PWD/../ExternalLibs/IDS/Lib/ -luEye_tools_64
unix|win32: LIBS += -L$$PWD/../ExternalLibs/IDS/Lib/ -luEye_tools
unix|win32: LIBS += -L$$PWD/../ExternalLibs/IDS/Lib/ -luEye_api_64
unix|win32: LIBS += -L$$PWD/../ExternalLibs/IDS/Lib/ -luEye_api

INCLUDEPATH += $$PWD/../ExternalLibs/IDS/include
DEPENDPATH += $$PWD/../ExternalLibs/IDS/include


QMAKE_CFLAGS_RELEASE += -Zi
QMAKE_CXXFLAGS_RELEASE += -Zi
QMAKE_LFLAGS_RELEASE += /DEBUG /OPT:REF



! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}


