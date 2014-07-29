#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T13:34:53
#
#-------------------------------------------------

QT       += gui widgets
#CONFIG   += qxt

TARGET = KPPCommon
TEMPLATE = lib

DEFINES += KPPCOMMON_LIBRARY

win32:QMAKE_CXXFLAGS += /DNOMINMAX

SOURCES += kppcommon.cpp \
    kppeditbox.cpp \
    kppframe.cpp \
    kppgestureframe.cpp \
    kpppushbutton.cpp \
    slidewidget.cpp \
    SlidingStackedWidget.cpp \
    swipegesturerecognizer.cpp \
    kppadjustablelistview.cpp \
    kpptreewidgetitem.cpp \
    kpproottreepushbutton.cpp

    kppadjustablelistview.cpp


  SOURCES += crashhandler.cpp
   SOURCES += crashdialog.cpp


HEADERS += kppcommon.h\
        kppcommon_global.h \
    kppeditbox.h \
    kppframe.h \
    kppgestureframe.h \
    kpppushbutton.h \
    slidewidget.h \
    SlidingStackedWidget.h \
    swipegesturerecognizer.h \
    kppadjustablelistview.h \
    kpptreewidgetitem.h \
    kpproottreepushbutton.h

    kppadjustablelistview.h


   HEADERS += crashhandler.h
   HEADERS += crashdialog.h





QMAKE_CFLAGS_RELEASE += -Zi
win32:QMAKE_CXXFLAGS_RELEASE += -Zi
win32:QMAKE_LFLAGS_RELEASE += /DEBUG /OPT:REF



FORMS += \
    crashdialog.ui

! include( ../common.pri ) {
    error( "Couldn't find the common.pri file!" )
}

! include( kppcommon.pri ) {
    error( "Couldn't find the kppcommon.pri file!" )
}




