#include "kppstyleditemdelegate.h"
#include "kpptreewidgetitem.h"
#include "QDebug"
#include "QStandardItem"



KPPStyledItemDelegate::KPPStyledItemDelegate(QWidget *parent, int hintval) :
    QStyledItemDelegate(parent)
{

}


void KPPStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    if (index.data(Qt::UserRole).toInt() == 1) {
        // parent item
    }
    if (index.data(Qt::UserRole).toInt() == 2) {
        //qDebug()<<"rect:"<<option.rect;

    }

    QStyledItemDelegate::paint(painter, option, index);
}

QSize KPPStyledItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{


    QSize newsize=QStyledItemDelegate::sizeHint(option, index);
    if (index.data(Qt::UserRole).toInt() == 2) {




        //newsize.setHeight(option.rect.height());



    }

    return newsize;
}
