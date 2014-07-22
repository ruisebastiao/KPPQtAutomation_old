#ifndef KPPTREEWIDGETITEM_H
#define KPPTREEWIDGETITEM_H

#include "kppcommon_global.h"
#include <QTreeWidgetItem>

class KPPCOMMONSHARED_EXPORT KPPTreeWidgetItem : public QTreeWidgetItem
{

public:
    explicit KPPTreeWidgetItem(int type=Type);

    bool isCollapseExpanding() const;
    void setIsCollapseExpanding(bool isCollapseExpanding);

private:
    bool m_isCollapseExpanding;
signals:

public slots:

};

#endif // KPPTREEWIDGETITEM_H
