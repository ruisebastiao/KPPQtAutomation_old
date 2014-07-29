#ifndef KPPCOMMON_H
#define KPPCOMMON_H

#include "kppcommon_global.h"
#include "QString"

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

class KPPCOMMONSHARED_EXPORT QStringSerializable{

public:
    QStringSerializable(QString QStringName, QString *QStringValue);

    QString *getQStringValue() const;
    void setStringValue(QString &value) const;
    std::string getQStringName() const ;

private:
    QString *m_QStringValue;
    QString m_QStringName;
};

#endif // KPPCOMMON_H
