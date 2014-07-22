#include "kpptreewidgetitem.h"

KPPTreeWidgetItem::KPPTreeWidgetItem(int type) :
    QTreeWidgetItem(type)
{
    m_isCollapseExpanding=false;

}

bool KPPTreeWidgetItem::isCollapseExpanding() const
{
    return m_isCollapseExpanding;
}

void KPPTreeWidgetItem::setIsCollapseExpanding(bool isCollapseExpanding)
{
    m_isCollapseExpanding = isCollapseExpanding;


}

