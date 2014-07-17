#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T13:34:53
#
#-------------------------------------------------

QT       += widgets
#CONFIG   += qxt

TARGET = KPPCommon
TEMPLATE = lib

DEFINES += KPPCOMMON_LIBRARY

SOURCES += kppcommon.cpp \
    kppeditbox.cpp \
    kppframe.cpp \
    kppgestureframe.cpp \
    kpppushbutton.cpp \
    slidewidget.cpp \
    SlidingStackedWidget.cpp \
    swipegesturerecognizer.cpp \

    kppadjustablelistview.cpp

win32{
  SOURCES += crashhandler.cpp
    SOURCES += crashdialog.cpp
}


HEADERS += kppcommon.h\
        kppcommon_global.h \
    kppeditbox.h \
    kppframe.h \
    kppgestureframe.h \
    kpppushbutton.h \
    slidewidget.h \
    SlidingStackedWidget.h \
    swipegesturerecognizer.h \

    kppadjustablelistview.h

win32{
   HEADERS += crashhandler.h
   HEADERS += crashdialog.h
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32: LIBS += -L$$PWD/../ExternalLibs/dbghelp/lib/ -ldbghelp

INCLUDEPATH += $$PWD/../ExternalLibs/dbghelp/include
DEPENDPATH += $$PWD/../ExternalLibs/dbghelp/include

QMAKE_CFLAGS_RELEASE += -Zi
QMAKE_CXXFLAGS_RELEASE += -Zi
QMAKE_LFLAGS_RELEASE += /DEBUG /OPT:REF



FORMS += \
    crashdialog.ui

! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCored
else:unix,android: LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCore

INCLUDEPATH += $$PWD/../ExternalLibs/Qxt/include
DEPENDPATH += $$PWD/../ExternalLibs/Qxt/include
