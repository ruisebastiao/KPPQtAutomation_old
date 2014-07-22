#ifndef KPPSTYLEDITEMDELEGATE_H
#define KPPSTYLEDITEMDELEGATE_H

#include "kppvision_global.h"
#include <QStyledItemDelegate>
#include "QTreeWidgetItem"


class KPPVISIONSHARED_EXPORT KPPStyledItemDelegate : public QStyledItemDelegate
{

    Q_OBJECT
public:
    explicit KPPStyledItemDelegate(QWidget *parent = 0,int hintval=100);

private:

signals:
    //void sizeHintChanged( const QModelIndex &index);
public slots:


    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

};

#endif // KPPSTYLEDITEMDELEGATE_H
