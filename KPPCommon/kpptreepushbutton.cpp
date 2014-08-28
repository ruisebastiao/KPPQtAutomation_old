#include "kpptreepushbutton.h"
#include "QDebug"

KPPRootTreePushButton::KPPRootTreePushButton(QString text,QTreeWidgetItem *widgetitem,QWidget *parent) :
    QPushButton(text,parent),
    m_WasGesture(false)
{

    setObjectName(text);
    m_widgetItem=widgetitem;

    //connect(m_widgetItem->treeWidget(),SIGNAL(expanded(QModelIndex))
    connect(this,SIGNAL(clicked()),this,SLOT(ButtonClickedSlot()));
    setAttribute(Qt::WA_AcceptTouchEvents,true);
    grabGesture(Qt::SwipeGesture);
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

void KPPRootTreePushButton::SetExpandItem(bool value){
    m_widgetItem->setExpanded(value);
}

void KPPRootTreePushButton::ButtonClickedSlot(){


    //QList<KPPRootTreePushButton *> allKPPRootTreePushButton = m_widgetItem->->tafindChildren<KPPRootTreePushButton *>();

    //    if(m_widgetItem->parent()!=0){
    //        for (int var = 0; var < m_widgetItem->parent()->childCount();++var) {

    //            if(m_widgetItem->parent()->child(var)!=m_widgetItem){
    //                m_widgetItem->parent()->child(var)->setExpanded(false);
    //            }
    //        }
    //    }
    if(!m_WasGesture){
        m_widgetItem->setExpanded(!m_widgetItem->isExpanded());

    }
    m_WasGesture=false;
}


bool KPPRootTreePushButton::event(QEvent *event)
{

    if (event->type() == QEvent::Gesture/*|| event->type()==QEvent::GestureOverride*/){

        //event->accept();


        return gestureEvent(static_cast<QGestureEvent*>(event));

    }
    if(event->type()==QEvent::MouseButtonPress){
         m_WasGesture=false;
    }
    // event->ignore();

    return QPushButton::event(event);
}

bool KPPRootTreePushButton::gestureEvent(QGestureEvent *event)
{



    if (QGesture *swipe = event->gesture(Qt::SwipeGesture)){
        swipeTriggered(static_cast<QSwipeGesture *>(swipe));



    }


    return true;
}

void KPPRootTreePushButton::setExpandOthers(bool value){
    QList<KPPRootTreePushButton *> allKPPRootTreePushButton = m_widgetItem->treeWidget()->findChildren<KPPRootTreePushButton *>();


//    bool bellow=false;
//    for (int var = 0; var < allKPPRootTreePushButton.count(); ++var) {

//        if(allKPPRootTreePushButton[var]->objectName()==this->objectName()){
//            bellow=true;
//        }

//        if(bellow){
//            allKPPRootTreePushButton[var]->SetExpandItem(value);
//        }

//    }

    if(value) m_widgetItem->treeWidget()->expandAll();
    else m_widgetItem->treeWidget()->collapseAll();


}

bool
KPPRootTreePushButton::swipeTriggered(QSwipeGesture* pSwipe)
{
    if(pSwipe->state() == Qt::GestureStarted || pSwipe->state() == Qt::GestureCanceled){
        //qDebug()<<"Bt gesture started";
        m_WasGesture=false;

    }

    if (pSwipe->state() == Qt::GestureFinished) {
        m_WasGesture=true;
        qreal  swipeangle=pSwipe->swipeAngle();

        if (pSwipe->verticalDirection()== QSwipeGesture::Up &&
                (swipeangle>45 && swipeangle<120)){

            setExpandOthers(false);

        }
        else if(pSwipe->verticalDirection() == QSwipeGesture::Down &&
                (swipeangle>=210 && swipeangle<320) ){
            setExpandOthers(true);
        }
        else{

            return false;
        }

        return true;
    }
    return false;
}
