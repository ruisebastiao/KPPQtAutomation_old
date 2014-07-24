#ifndef ILISTVIEWITEM_H
#define ILISTVIEWITEM_H

#include "kppvision_global.h"

class KPPVISIONSHARED_EXPORT IListViewItem
{
public:
    virtual QString getName()=0;
    virtual void setName(const QString &name)=0;
    virtual ~IListViewItem() {}
    //IListViewItem();
};

#endif // ILISTVIEWITEM_H
