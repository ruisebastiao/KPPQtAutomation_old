

win32: LIBS += -L$$PWD/../ExternalLibs/dbghelp/lib/ -ldbghelp

INCLUDEPATH += $$PWD/../ExternalLibs/dbghelp/include
DEPENDPATH += $$PWD/../ExternalLibs/dbghelp/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCored
else:unix,android: LIBS += -L$$PWD/../ExternalLibs/Qxt/lib/ -lQxtCore

INCLUDEPATH += $$PWD/../ExternalLibs/Qxt/include
DEPENDPATH += $$PWD/../ExternalLibs/Qxt/include
