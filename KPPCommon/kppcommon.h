#ifndef KPPCOMMON_H
#define KPPCOMMON_H

#include "kppcommon_global.h"

class KPPCOMMONSHARED_EXPORT KPPCommon
{

public:
    KPPCommon();
    static QString loadStyleSheet(const QString &aliasname);
};

#endif // KPPCOMMON_H
