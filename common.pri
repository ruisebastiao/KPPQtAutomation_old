#Includes common configuration for all subdirectory .pro files.
INCLUDEPATH += . .. $$PWD
WARNINGS += -Wall

TEMPLATE = lib


# The following keeps the generated files at least somewhat separate 
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

INCLUDEPATH += $$PWD/../ExternalLibs/Qxt/include
DEPENDPATH += $$PWD/../ExternalLibs/Qxt/include

INCLUDEPATH += C:/boost/boost_1_55_0
LIBS += -LC:/boost/boost_1_55_0/stage/lib/
