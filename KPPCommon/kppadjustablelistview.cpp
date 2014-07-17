#include "kppadjustablelistview.h"
#include "QHBoxLayout"
#include <QScrollArea>
#include "QDebug"
#include "QPropertyAnimation"
#include "qevent.h"


KPPAdjustableListView::KPPAdjustableListView(QWidget *parent) :
    QListView(parent)

{

    setItemDelegate(new QAdjustableListItemDelegate(this));
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff)   ;
    //setMinimumHeight(150);

   // sizePolicy().setVerticalPolicy(QSizePolicy::Preferred);
    //setSizeAdjustPolicy(AdjustToContents);
    //setResizeMode(ResizeMode::Adjust);

    AdjustContents(0);
}


void KPPAdjustableListView::AdjustContents(int finalValue,QEasingCurve animStyle){
    int rc =0;
    if(model()!=0)
      rc=model()->rowCount();

    int start=height();
    int end=rc ? rc*sizeHintForRow(0):0;
    end+=5;

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

//    if(height()<250){
//        return QSize(size.width(),250);
//    }
//    else
        //return QSize(parentWidget()->width(),size.height());
        //size.setHeight(500);
        return size;

}

void KPPAdjustableListView::rowsInserted(const QModelIndex &parent, int start, int end)
{
    AdjustContents();
    QListView::rowsInserted(parent,start,end);

}



void KPPAdjustableListView::dataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
   // QListView::dataChanged(topLeft,bottomRight,roles);
    //QListView::dataChanged(topLeft,bottomRight,roles);
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

