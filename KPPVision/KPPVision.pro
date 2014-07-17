#-------------------------------------------------
#
# Project created by QtCreator 2014-07-17T16:51:46
#
#-------------------------------------------------

QT       += gui widgets xml

TARGET = KPPVision
TEMPLATE = lib

DEFINES += KPPVISION_LIBRARY

SOURCES += kppvision.cpp \
    inspection.cpp

HEADERS += kppvision.h\
        kppvision_global.h \
    inspection.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../icxmlserializable/release/ -licxmlserializable
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../icxmlserializable/debug/ -licxmlserializable
else:unix: LIBS += -L$$PWD/../icxmlserializable/ -licxmlserializable

INCLUDEPATH += $$PWD/../icxmlserializable
DEPENDPATH += $$PWD/../icxmlserializable


unix {
    target.path = /usr/lib
    INSTALLS += target
}

! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}
