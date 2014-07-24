#ifndef REQUEST_H
#define REQUEST_H

#include "kppvision_global.h"
#include "icxmlserializable.h"
#include "ilistviewitem.h"
#include "kppvisionlist.h"
#include "inspection.h"

namespace Vision {


class KPPVISIONSHARED_EXPORT Request :public icXmlSerializable, public IListViewItem
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);

private:
    QString m_Name;
    KPPVisionList<Inspection> *m_Inspections;
signals:

public slots:


    // icXmlSerializable interface
protected:
    bool deserialize();
    bool serialize();

    // IVisionListItem interface
public:
    QString getName();
    void setName(const QString &name);
    KPPVisionList<Inspection> *Inspections() const;

};
}
#endif // REQUEST_H
