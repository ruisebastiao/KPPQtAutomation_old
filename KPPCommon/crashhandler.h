#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H

#ifdef _WIN32
#include <Windows.h>
#include <imagehlp.h>
#endif

#include <iostream>
#include "qdebug.h"
#include "qmessagebox.h"
#include "kppcommon_global.h"

namespace CrashReport {

    #ifdef _WIN32
    KPPCOMMONSHARED_EXPORT void windows_print_stacktrace(CONTEXT* context);
    KPPCOMMONSHARED_EXPORT LONG WINAPI windows_exception_handler(EXCEPTION_POINTERS * ExceptionInfo);
    #endif
}
#endif // CRASHHANDLER_H
