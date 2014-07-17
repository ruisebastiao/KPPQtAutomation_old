#ifndef CRASHHANDLER_H
#define CRASHHANDLER_H
#include <Windows.h>
#include <iostream>
#include <imagehlp.h>
#include "qdebug.h"
#include "qmessagebox.h"
#include "kppcommon_global.h"

namespace CrashReport {

    KPPCOMMONSHARED_EXPORT void windows_print_stacktrace(CONTEXT* context);
    KPPCOMMONSHARED_EXPORT LONG WINAPI windows_exception_handler(EXCEPTION_POINTERS * ExceptionInfo);

}
#endif // CRASHHANDLER_H
