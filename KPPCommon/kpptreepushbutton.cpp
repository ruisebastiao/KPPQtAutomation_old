#include "kpptreepushbutton.h"

KPPRootTreePushButton::KPPRootTreePushButton(QString text,QTreeWidgetItem *widgetitem,QWidget *parent) :
    QPushButton(text,parent)
{

    setObjectName(text);
    m_widgetItem=widgetitem;
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClickedSlot()));
}

void KPPRootTreePushButton::setText(const QString &text)
{
    QPushButton::setText(text);
    setObjectName(text);
}
QTreeWidgetItem *KPPRootTreePushButton::widgetItem() const
{
    return m_widgetItem;
}


void KPPRootTreePushButton::ButtonClickedSlot(){


    //QList<KPPRootTreePushButton *> allKPPRootTreePushButton = m_widgetItem->->tafindChildren<KPPRootTreePushButton *>();

    if(m_widgetItem->parent()!=0){
        for (int var = 0; var < m_widgetItem->parent()->childCount();++var) {

            if(m_widgetItem->parent()->child(var)!=m_widgetItem){
                m_widgetItem->parent()->child(var)->setExpanded(false);
            }
        }
    }

    m_widgetItem->setExpanded(!m_widgetItem->isExpanded());
}
