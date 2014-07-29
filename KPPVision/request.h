#ifndef REQUEST_H
#define REQUEST_H

#include "kppvision_global.h"
#include "ilistviewitem.h"
#include "kppvisionlist.h"
#include "inspection.h"

namespace Vision {



class KPPVISIONSHARED_EXPORT Request:public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);

private:
    QString m_Name;
    KPPVisionList<Inspection> *m_Inspections;
signals:

public slots:




    // IVisionListItem interface
public:
    QString getName();
    void setName(const QString &name);
    KPPVisionList<Inspection> *Inspections() const;


    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
};
}
#endif // REQUEST_H
