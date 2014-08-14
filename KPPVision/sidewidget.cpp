#include "sidewidget.h"
#include<qlayout.h>
#include <QtGui>
SideWidget::SideWidget(QWidget *parent) :
    QWidget(parent)
{

   lostFocustoChild=false;
   setMenuState(Closed);

}
SideWidget::State SideWidget::getMenuState() const
{
    return menuState;
}

SideWidget::State SideWidget::toogleMenuState(){

    if(getMenuState()==Opened){
        setMenuState(Closed);
    }
    else {
        setMenuState(Opened);
    }

    return getMenuState();
}





void SideWidget::setMenuState(const State &value)
{
    int start=0;
    int end =250;
    //QRect start;
    //QRect end;



  //  start= QRect(0, 0, 0, sizeHint().height());
    //end=QRect(0, 0, sizeHint().width(), sizeHint().height());

    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "maximumWidth");
    connect(animation1,SIGNAL(finished()),parentWidget(),SLOT(update()));
    //QPropertyAnimation *animation1 = new QPropertyAnimation(this, "geometry");
    animation1->setDuration(250);
    switch (value) {
    case Opened:
       animation1->setStartValue(start);
        animation1->setEndValue(end);
        lostFocustoChild=false;
        this->setFocus();
        break;
    case Closed:
        animation1->setStartValue(end);
        animation1->setEndValue(start);


        break;


    default:
        break;
    }



    animation1->start();

    menuState = value;
}


void SideWidget::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

