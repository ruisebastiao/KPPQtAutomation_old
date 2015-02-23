#Includes common configuration for all subdirectory .pro files.
INCLUDEPATH += . .. $$PWD
WARNINGS += -Wall




# The following keeps the generated files at least somewhat separate 
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

INCLUDEPATH += $$PWD/../ExternalLibs/Qxt/include
DEPENDPATH += $$PWD/../ExternalLibs/Qxt/include

INCLUDEPATH += $$PWD/../ExternalLibs/boost
LIBS += -L$$PWD/../ExternalLibs/boost/lib

INCLUDEPATH += $$PWD/../ExternalLibs/IDS/include

unix|win32: LIBS += -L$$PWD/../ExternalLibs/IDS/Lib/ -luEye_tools_64
unix|win32: LIBS += -L$$PWD/../ExternalLibs/IDS/Lib/ -luEye_tools
unix|win32: LIBS += -L$$PWD/../ExternalLibs/IDS/Lib/ -luEye_api_64
unix|win32: LIBS += -L$$PWD/../ExternalLibs/IDS/Lib/ -luEye_api


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core249 -lopencv_imgproc249 -lopencv_highgui249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core249d -lopencv_imgproc249d -lopencv_highgui249d
else:unix: LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core249


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCore -lQxtWidgets
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCored -lQxtWidgetsd
else:unix: LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCore

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ExternalLibs/dbghelp/lib/ -ldbghelp -ldbghelp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ExternalLibs/dbghelp/lib/ -ldbghelp -ldbghelp
else:unix: LIBS += -L$$PWD/../ExternalLibs/dbghelp/lib/ -ldbghelp

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core300 -lopencv_imgproc300 -lopencv_highgui300
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core300d -lopencv_imgproc300d -lopencv_highgui300d
#else:unix: LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core300

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core249 -lopencv_imgproc249 -lopencv_highgui249
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core249d -lopencv_imgproc249d -lopencv_highgui249d
else:unix: LIBS += -L$$PWD/../ExternalLibs/OpenCV/lib/ -lopencv_core249


INCLUDEPATH += $$PWD/../ExternalLibs/OpenCV/include
DEPENDPATH += $$PWD/../ExternalLibs/OpenCV/include
