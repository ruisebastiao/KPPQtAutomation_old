#ifndef REQUEST_H
#define REQUEST_H

#include "kppvision_global.h"
#include "icxmlserializable.h"

class KPPVISIONSHARED_EXPORT Request : public icXmlSerializable
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);

private:
    QString m_Name;
signals:

public slots:


    // icXmlSerializable interface
protected:
    bool deserialize();
    bool serialize();

    // IVisionListItem interface
public:
    QString getName();

    // IVisionListItem interface
public:
    void setName(const QString &name);
};

#endif // REQUEST_H
