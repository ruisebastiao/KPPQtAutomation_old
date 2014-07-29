#ifndef KPPVISIONLIST_H
#define KPPVISIONLIST_H

#include "kppvision_global.h"
#include "qabstractitemmodel.h"


namespace Vision {



template<class T>
class KPPVISIONSHARED_EXPORT KPPVisionList :public QAbstractListModel
{

public:
    explicit KPPVisionList(QObject *parent = 0);

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


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    // QAbstractItemModel interface
public:
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QModelIndex getItemModelIndex(T *Item);
};

}

#endif // KPPVISIONLIST_H
