
#include "crashhandler.h"
#include "crashdialog.h"

#include <QxtCore/QxtLogger>
#include <QxtCore/QxtXmlFileLoggerEngine>

namespace CrashReport {

   #ifdef _WIN32

void windows_print_stacktrace(CONTEXT* context)
{
    QStringList msgs;
    SymInitialize(GetCurrentProcess(), 0, true);

    STACKFRAME frame = { 0 };

    /* setup initial stack frame */
    frame.AddrPC.Offset         = context->Eip;
    frame.AddrPC.Mode           = AddrModeFlat;
    frame.AddrStack.Offset      = context->Esp;
    frame.AddrStack.Mode        = AddrModeFlat;
    frame.AddrFrame.Offset      = context->Ebp;
    frame.AddrFrame.Mode        = AddrModeFlat;

    while (StackWalk(IMAGE_FILE_MACHINE_I386 ,
                     GetCurrentProcess(),
                     GetCurrentThread(),
                     &frame,
                     context,
                     0,
                     SymFunctionTableAccess,
                     SymGetModuleBase,
                     0 ) )
    {
        //------------------------------------------------------------------
        // Declare an image help symbol structure to hold symbol info and
        // name up to 256 chars This struct is of variable lenght though so
        // it must be declared as a raw byte buffer.
        //------------------------------------------------------------------

        static char symbolBuffer[ sizeof(IMAGEHLP_SYMBOL) + 255 ];

        memset( symbolBuffer , 0 , sizeof(IMAGEHLP_SYMBOL) + 255 );

        // Cast it to a symbol struct:

        IMAGEHLP_SYMBOL * symbol = (IMAGEHLP_SYMBOL*) symbolBuffer;

        // Need to set the first two fields of this symbol before obtaining name info:

        symbol->SizeOfStruct    = sizeof(IMAGEHLP_SYMBOL) + 255;
        symbol->MaxNameLength   = 254;



        // Need to set the first two fields of this symbol before obtaining name info:

        symbol->SizeOfStruct    = sizeof(IMAGEHLP_SYMBOL) + 255;
        symbol->MaxNameLength   = 254;

        // The displacement from the beginning of the symbol is stored here: pretty useless



        static char lineBuffer[ sizeof(IMAGEHLP_LINE) + 255 ];

        memset( lineBuffer , 0 , sizeof(IMAGEHLP_LINE) + 255 );

        IMAGEHLP_LINE * line = (IMAGEHLP_LINE*) lineBuffer;

        line->SizeOfStruct    = sizeof(IMAGEHLP_SYMBOL) + 255;
        //line->MaxNameLength   = 254;


        unsigned displacement = 0;

        // Get the symbol information from the address of the instruction pointer register:

        if
                (
                 SymGetSymFromAddr
                 (
                     GetCurrentProcess()     ,   // Process to get symbol information for
                     frame.AddrPC.Offset     ,   // Address to get symbol for: instruction pointer register
                     (DWORD*) & displacement ,   // Displacement from the beginning of the symbol: whats this for ?
                     symbol                      // Where to save the symbol
                     )
                 )
        {
            // Add the name of the function to the function list:

            SymGetLineFromAddr(GetCurrentProcess(),frame.AddrPC.Offset,(DWORD*) & displacement,line);



            if(line->LineNumber!=0){
                QString newmsg=QString("at ").append(line->FileName).append(" Line:%1").arg(line->LineNumber);
                msgs.append(newmsg);
            }

        }
        else
        {
//            // Print an unknown location:

//            // functionNames.push_back("unknown location");

//            char buffer[64];
//            sprintf( buffer , "0x%08x" ,  frame.AddrPC.Offset );
//            qDebug()<<buffer;
            // functionNames.push_back(buffer);
        }
        // addr2line(icky_global_program_name, (void*)frame.AddrPC.Offset);
    }
    qxtLog->fatal()<<msgs.join('\n');
    CrashDialog dialog;
    dialog.setMessage(msgs);
    dialog.exec();




    //QMessageBox::warning(0,QString("outch"),QString("outch"));

    SymCleanup( GetCurrentProcess() );
}

LONG WINAPI windows_exception_handler(EXCEPTION_POINTERS * ExceptionInfo)
{
    switch(ExceptionInfo->ExceptionRecord->ExceptionCode)
    {
    case EXCEPTION_ACCESS_VIOLATION:
        qxtLog->debug()<<"Error: EXCEPTION_ACCESS_VIOLATION\n";
        break;
    case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
        qxtLog->debug()<<"Error: EXCEPTION_ARRAY_BOUNDS_EXCEEDED\n";
        break;
    case EXCEPTION_BREAKPOINT:
        qxtLog->debug()<<"Error: EXCEPTION_BREAKPOINT\n";
        break;
    case EXCEPTION_DATATYPE_MISALIGNMENT:
        qxtLog->debug()<<"Error: EXCEPTION_DATATYPE_MISALIGNMENT\n";
        break;
    case EXCEPTION_FLT_DENORMAL_OPERAND:
        qxtLog->debug()<<"Error: EXCEPTION_FLT_DENORMAL_OPERAND\n";
        break;
    case EXCEPTION_FLT_DIVIDE_BY_ZERO:
        qxtLog->debug()<<"Error: EXCEPTION_FLT_DIVIDE_BY_ZERO\n";
        break;
    case EXCEPTION_FLT_INEXACT_RESULT:
        qxtLog->debug()<<"Error: EXCEPTION_FLT_INEXACT_RESULT\n";
        break;
    case EXCEPTION_FLT_INVALID_OPERATION:
        qxtLog->debug()<<"Error: EXCEPTION_FLT_INVALID_OPERATION\n";
        break;
    case EXCEPTION_FLT_OVERFLOW:
        qxtLog->debug()<<"Error: EXCEPTION_FLT_OVERFLOW\n";
        break;
    case EXCEPTION_FLT_STACK_CHECK:
        qxtLog->debug()<<"Error: EXCEPTION_FLT_STACK_CHECK\n";
        break;
    case EXCEPTION_FLT_UNDERFLOW:
        qxtLog->debug()<<"Error: EXCEPTION_FLT_UNDERFLOW\n";
        break;
    case EXCEPTION_ILLEGAL_INSTRUCTION:
        qxtLog->debug()<<"Error: EXCEPTION_ILLEGAL_INSTRUCTION\n";
        break;
    case EXCEPTION_IN_PAGE_ERROR:
        qxtLog->debug()<<"Error: EXCEPTION_IN_PAGE_ERROR\n";
        break;
    case EXCEPTION_INT_DIVIDE_BY_ZERO:
        qxtLog->debug()<<"Error: EXCEPTION_INT_DIVIDE_BY_ZERO\n";
        break;
    case EXCEPTION_INT_OVERFLOW:
        qxtLog->debug()<<"Error: EXCEPTION_INT_OVERFLOW\n";
        break;
    case EXCEPTION_INVALID_DISPOSITION:
        qxtLog->debug()<<"Error: EXCEPTION_INVALID_DISPOSITION\n";
        break;
    case EXCEPTION_NONCONTINUABLE_EXCEPTION:
        qxtLog->debug()<<"Error: EXCEPTION_NONCONTINUABLE_EXCEPTION\n";
        break;
    case EXCEPTION_PRIV_INSTRUCTION:
        qxtLog->debug()<<"Error: EXCEPTION_PRIV_INSTRUCTION\n";
        break;
    case EXCEPTION_SINGLE_STEP:
        qxtLog->debug()<<"Error: EXCEPTION_SINGLE_STEP\n";
        break;
    case EXCEPTION_STACK_OVERFLOW:
        qxtLog->debug()<<"Error: EXCEPTION_STACK_OVERFLOW\n";
        break;
    default:
        qxtLog->debug()<<"Error: Unrecognized Exception\n";
        break;
    }
    //fflush(stderr);
    /* If this is a stack overflow then we can't walk the stack, so just show
    where the error happened */
    if (EXCEPTION_STACK_OVERFLOW != ExceptionInfo->ExceptionRecord->ExceptionCode)
    {

        windows_print_stacktrace(ExceptionInfo->ContextRecord);
    }
    else
    {
        //  addr2line(icky_global_program_name, (void*)ExceptionInfo->ContextRecord->Eip);
    }



    return EXCEPTION_EXECUTE_HANDLER;
}

#endif
}


