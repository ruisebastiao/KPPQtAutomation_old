#include "kppcommon.h"
#include "qfile.h"
#include "QTextStream.h"

KPPCommon::KPPCommon()
{
}



QString KPPCommon::loadStyleSheet(const QString &aliasname) {
    /* Let's use QFile and point to a resource... */
    QFile data(aliasname);
    //QFile data(":/darkorange");
    QString style;
    /* ...to open the file */
    if(data.open(QFile::ReadOnly)) {
        /* QTextStream... */
        QTextStream styleIn(&data);
        /* ...read file to a string. */
        style = styleIn.readAll();
        data.close();
        /* We'll use qApp macro to get the QApplication pointer
         * and set the style sheet application wide. */
        return style;
    }

    return "";
}
