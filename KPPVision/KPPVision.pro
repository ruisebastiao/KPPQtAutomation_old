#-------------------------------------------------
#
# Project created by QtCreator 2014-07-17T16:51:46
#
#-------------------------------------------------

QT       += gui widgets xml

TARGET = KPPVision
TEMPLATE = lib

DEFINES += KPPVISION_LIBRARY

QMAKE_CXXFLAGS += /DNOMINMAX

SOURCES += kppvision.cpp \
    inspection.cpp \
    configurationswidget.cpp \
    sidewidget.cpp \
    SizeGripItem.cpp \
    settings.cpp \
    visiontreewidget.cpp \
    kppstyleditemdelegate.cpp \
    kppvisionlist.cpp \
    request.cpp \
    ilistviewitem.cpp \
    inspectiontreewidget.cpp \
    capturesource.cpp \
    imagefilecapture.cpp \
    requestmenu.cpp \
    inspectionmenu.cpp \
    kpproi.cpp \
    resizableitem.cpp \
    kppgraphicsview.cpp \
    kppgraphicsscene.cpp \
    imageholder.cpp \
    kppvisionauxfunctions.cpp \
    visionwindow.cpp

HEADERS += kppvision.h\
        kppvision_global.h \
    inspection.h \
    configurationswidget.h \
    sidewidget.h \
    SizeGripItem.h \
    settings.h \    
    visiontreewidget.h \
    kppstyleditemdelegate.h \
    kppvisionlist.h \
    request.h \
    ilistviewitem.h \
    inspectiontreewidget.h \
    capturesource.h \
    imagefilecapture.h \
    BoostDef.h \
    requestmenu.h \
    inspectionmenu.h \
    kpproi.h \
    resizableitem.h \
    kppgraphicsview.h \
    kppgraphicsscene.h \
    imageholder.h \
    kppvisionauxfunctions.h \
    visionwindow.h



unix {
    target.path = /usr/lib
    INSTALLS += target
}


! include( ../common.pri ) {
    error( "Couldn't find the kppcommon.pri file!" )
    }



FORMS += \
    configurationswidget.ui \
    requestmenu.ui \
    inspectionmenu.ui \
    visionwindow.ui

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




RESOURCES += \
    resources/visionres.qrc
