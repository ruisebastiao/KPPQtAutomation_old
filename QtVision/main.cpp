#include "mainwindow.h"
#include <QApplication>
#include "qmessagebox.h"
#include "settings.h"
#include "qstandardpaths.h"
#include "qdebug.h"
#include "crashhandler.h"
#include "kppcommon.h"
#include <QxtCore/QxtBasicFileLoggerEngine>
#include <QxtCore/QxtLogger>
#include <QxtCore/QxtXmlFileLoggerEngine>
#include "qobject.h"

using namespace CrashReport;

//using namespace std;


void setupLogger(QString path="")
{
    QString loc="";
    if(path==""){
         loc=qApp->applicationDirPath().append("/");//QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    }
    else
        loc=path;



    QxtXmlFileLoggerEngine *dbg  = new QxtXmlFileLoggerEngine(QString().append(loc).append("debug.log"));
    QxtXmlFileLoggerEngine *info = new QxtXmlFileLoggerEngine(QString().append(loc).append("info.log"));



    // qxtLog takes ownership of dbg - no need to manage its memory
    qxtLog->addLoggerEngine("dbg", dbg);
    qxtLog->addLoggerEngine("app", info);

    qxtLog->disableAllLogLevels();

    qxtLog->enableLogLevels("dbg", QxtLogger::AllLevels);
    qxtLog->enableLogLevels("app",  QxtLogger::InfoLevel | QxtLogger::WarningLevel | QxtLogger::ErrorLevel | QxtLogger::CriticalLevel | QxtLogger::FatalLevel | QxtLogger::WriteLevel );
}

int main(int argc, char *argv[])
{


    // Adiciona callback para erros indefinidos
    SetUnhandledExceptionFilter(windows_exception_handler);


    QApplication a(argc, argv);

    setupLogger();



    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    qApp->installTranslator(&qtTranslator);


    QTranslator *translator= new QTranslator;

    translator->load(":/language/entr_pt_qm");
    qApp->installTranslator(translator);


   // qxtLog->info()<<translator->tr("Initializing application...");


    MainWindow w;


    qApp->setStyleSheet(KPPCommon::loadStyleSheet(":/glossy"));

    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint) ;

    w.showMaximized();



    QObject::connect(&a, SIGNAL(focusChanged(QWidget*,QWidget*)), &w, SLOT(focusChanged(QWidget*,QWidget*)));



    const int r=a.exec();



    return r;




}
