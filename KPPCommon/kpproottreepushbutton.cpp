#include "kpproottreepushbutton.h"

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


    QList<KPPRootTreePushButton *> allKPPRootTreePushButton = m_widgetItem->treeWidget()->findChildren<KPPRootTreePushButton *>();

    for (int var = 0; var < allKPPRootTreePushButton.count(); ++var) {
        if(allKPPRootTreePushButton[var]->objectName()!=objectName()){
            allKPPRootTreePushButton[var]->widgetItem()->setExpanded(false);
        }
    }

    m_widgetItem->setExpanded(!m_widgetItem->isExpanded());
}
