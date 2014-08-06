#include "kppadjustablelistview.h"
#include "QHBoxLayout"
#include <QScrollArea>
#include "QDebug"
#include "QPropertyAnimation"
#include "qevent.h"
#include "qapplication.h"
#include "kppcommon.h"

KPPAdjustableListView::KPPAdjustableListView(QWidget *parent) :
    QListView(parent)

{

    setItemDelegate(new QAdjustableListItemDelegate(this));
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff)   ;
    sizePolicy().setHorizontalPolicy(QSizePolicy::Maximum);
    sizePolicy().setVerticalPolicy(QSizePolicy::Maximum);
    AdjustContents(0);




     setAttribute(Qt::WA_AcceptTouchEvents,true);
}

void KPPAdjustableListView::setGrabEnable(bool enable){
    if(enable){
        grabGesture(Qt::SwipeGesture);
    }
    else
        ungrabGesture(Qt::SwipeGesture);

}

bool KPPAdjustableListView::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture/*|| event->type()==QEvent::GestureOverride*/){


        return gestureEvent(static_cast<QGestureEvent*>(event));

    }

    return QListView::event(event);
    //return false;//
}

bool KPPAdjustableListView::gestureEvent(QGestureEvent *event)
{
    if (QGesture *swipe = event->gesture(Qt::SwipeGesture))
        swipeTriggered(static_cast<QSwipeGesture *>(swipe));

    return true;
}

void KPPAdjustableListView::swipeTriggered(QSwipeGesture *gesture)
{
//    int index = QObject::staticQtMetaObject.indexOfEnumerator("GestureState");
//    QMetaEnum metaEnum = QObject::staticQtMetaObject.enumerator(index);
//    QString temp= metaEnum.valueToKey(gesture->state());

//      qDebug()<<"KPPAdjustableListView state:"<<temp;
    if (gesture->state() == Qt::GestureFinished) {

        if (gesture->horizontalDirection() == QSwipeGesture::Left)
        {
            emit SwipedLeft();
        }
        else
        {
            emit SwipedRight();
        }

        //update();
    }
}

void KPPAdjustableListView::AdjustContents(int finalValue,QEasingCurve animStyle){



     setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff)   ;
    int rc =0;
    if(model()!=0)
      rc=model()->rowCount();

    int start=height();
    int end=rc ? rc*sizeHintForRow(0):0;
    end+=10;

    if(start==end) return;
    //setMinimumHeight(end-2);
    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "maximumHeight");

    connect(animation1,SIGNAL(finished()),SLOT(AnimationFinished()));
    animation1->setDuration(250);

    animation1->setStartValue(start);




    if(finalValue!=-1)
        end=finalValue;

    if(end==0)
        animStyle=QEasingCurve::InCirc;

    animation1->setEndValue(end);

    animation1->setEasingCurve(animStyle);

    animation1->start(QPropertyAnimation::DeleteWhenStopped);



    //qDebug()<<this->maximumHeight();
}


void KPPAdjustableListView::AnimationFinished(){


    //setGeometry(x(),y(),width(),maximumHeight());
    //parentWidget()->resize(parentWidget()->size());
    //parentWidget()->hide();
    //qDebug()<<parentWidget()->objectName();
   // if(parentWidget()->objectName()=="frame1")
   // adjustSize();
    if(parentWidget()!=0)
        parentWidget()->updateGeometry();
    //qDebug()<< resizeMode();
    if(size().height()<contentsSize().height()&& size().height()>0){

        setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded)   ;

    }
    else{

        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff)   ;
    }

    //adjustSize();
}

void KPPAdjustableListView::setModel(QAbstractItemModel *model)
{
    QItemSelectionModel *m=selectionModel();

    if(model!=0){
        connect(model,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(rowsRemoved(QModelIndex,int,int)));
        QListView::setModel(model);
    }



    AdjustContents();

}




QSize KPPAdjustableListView::sizeHint() const
{
    QSize size=QListView::sizeHint();

    if(model()!=0){
        int ct=model()->rowCount();
        size.setHeight(ct*sizeHintForRow(0)+15);
    }
    else
        size.setHeight(0);

    return size;

}

void KPPAdjustableListView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    AdjustContents();
    QListView::rowsInserted(parent,start,end);

}



void KPPAdjustableListView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{


    AdjustContents();

}

void KPPAdjustableListView::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

    QListView::selectionChanged(selected,deselected);
    emit selectionChangedSignal(selected,deselected);
}

void KPPAdjustableListView::rowsRemoved(const QModelIndex &parent, int first, int last)
{
     AdjustContents();
}



int KPPAdjustableListView::sizeHintForRow(int row) const
{
    return 50;
}
