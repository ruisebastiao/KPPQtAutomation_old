#ifndef KPPCOMMON_H
#define KPPCOMMON_H

#include "kppcommon_global.h"

#define ENUM_TO_STRING(c, e, v) \
    (c::staticMetaObject.enumerator(c::staticMetaObject.indexOfEnumerator(#e)).valueToKey(v))

#define STRING_TO_ENUM(c, e, s) \
    (c::e)(c::staticMetaObject.enumerator(c::staticMetaObject.indexOfEnumerator(#e)).keyToValue(s.toUtf8()))

class KPPCOMMONSHARED_EXPORT KPPCommon
{

public:
    KPPCommon();
    static QString loadStyleSheet(const QString &aliasname);
};

#endif // KPPCOMMON_H
