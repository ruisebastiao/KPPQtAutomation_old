#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T13:35:29
#
#-------------------------------------------------

QT       += core gui xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KPPAutomation
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11


#UI_DIR = uics
#MOC_DIR = mocs

#OBJECTS_DIR = objs

SOURCES += main.cpp\
        mainwindow.cpp \
    actionbar.cpp \    
    menustyle.cpp

HEADERS  += mainwindow.h \
    actionbar.h \
    menustyle.h \
    uics/ui_mainwindow.h

FORMS    +=mainwindow.ui

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../KPPCommon/release/ -lKPPCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../KPPCommon/debug/ -lKPPCommon
else:unix: LIBS += -L$$OUT_PWD/../KPPCommon/ -lKPPCommon

INCLUDEPATH += $$PWD/../KPPCommon
DEPENDPATH += $$PWD/../KPPCommon

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../KPPHardware/release/ -lKPPHardware
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../KPPHardware/debug/ -lKPPHardware
else:unix: LIBS += -L$$OUT_PWD/../KPPHardware/ -lKPPHardware

INCLUDEPATH += $$PWD/../KPPHardware
DEPENDPATH += $$PWD/../KPPHardware

INCLUDEPATH += $$PWD/../ExternalLibs/IDS/include

QMAKE_CFLAGS_RELEASE += -Zi
QMAKE_CXXFLAGS_RELEASE += -Zi
QMAKE_LFLAGS_RELEASE += /DEBUG /OPT:REF



RESOURCES += \
    resources/res.qrc





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../icxmlserializable/release/ -licxmlserializable
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../icxmlserializable/debug/ -licxmlserializable
else:unix: LIBS += -L$$PWD/../icxmlserializable/ -licxmlserializable

INCLUDEPATH += $$PWD/../icxmlserializable
DEPENDPATH += $$PWD/../icxmlserializable



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCored
else:unix: LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCore

INCLUDEPATH += $$PWD/../ExternalLibs/Qxt/include
DEPENDPATH += $$PWD/../ExternalLibs/Qxt/include


win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../KPPVision/release/ -lKPPVision
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../KPPVision/debug/ -lKPPVision
else:unix: LIBS += -L$$OUT_PWD/../KPPVision/ -lKPPVision

INCLUDEPATH += $$PWD/../KPPVision
DEPENDPATH += $$PWD/../KPPVision

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../icxmlserializable/release/ -licxmlserializable
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../icxmlserializable/debug/ -licxmlserializable
else:unix: LIBS += -L$$OUT_PWD/../icxmlserializable/ -licxmlserializable

INCLUDEPATH += $$PWD/../icxmlserializable
DEPENDPATH += $$PWD/../icxmlserializable

QMAKE_CXXFLAGS += /DNOMINMAX