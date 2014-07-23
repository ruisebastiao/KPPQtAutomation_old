#ifndef KPPVISIONLIST_H
#define KPPVISIONLIST_H

#include "kppvision_global.h"
#include "icxmlserializable.h"

namespace Vision {



template<class T>
class KPPVISIONSHARED_EXPORT KPPVisionList : public icXmlSerializable
{

public:
    explicit KPPVisionList(QObject *parent = 0,QString RootId="");

    QString getName() const;
    void setName(const QString &getName);

    QStringList getItemsNameList() const;
    QList<T *> getList();
    T *getItemByName(const QString &name) const;
    T *AddItem(const QString &name, QObject *parent=0);
    void removeItem(T *item);
private:
    QString m_Name;
    QList<T*>   m_InnerList;

signals:

public slots:


    // QAbstractItemModel interface
public:
    Qt::ItemFlags flags(const QModelIndex &index) const;

    // icXmlSerializable interface
protected:
    bool deserialize();
    bool serialize();

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    // QAbstractItemModel interface
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role);
};

}

#endif // KPPVISIONLIST_H
