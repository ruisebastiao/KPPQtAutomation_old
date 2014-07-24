#include "kpppushbutton.h"
#include "QResizeEvent"
#include "QApplication"

//#include "qabstractanimation.h"

KPPPushbutton::KPPPushbutton(QWidget *parent) :
    QPushButton(parent)
{
    ishover=false;
    defaultSize=0;
    m_visible=false;
    setVisible(true);

    this->setStyleSheet("QPushButton {\
                                border: 1px solid #6593cf;\
                                border-radius: 2px;\
                                padding: 5px 15px 2px 5px;\
                                background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #f5f9ff,\
                                        stop :   0.5 #c7dfff, stop :   0.55 #afd2ff, stop :   1.0 #c0dbff);\
                                color: #006aff;\
                                font: bold large 'Arial';\
                                height: 30px;\
                        }\
                        QPushButton:hover,QPushButton:hover:on{\
                                background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #ffd9aa,\
                                        stop :   0.5 #ffbb6e, stop :   0.55 #feae42, stop :   1.0 #fedb74);\
                        }\
                        QPushButton:pressed {\
                                background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #c0dbff,\
                                stop :   0.5 #cfd26f, stop :   0.55 #c7df6f, stop :   1.0 #f5f9ff);\
                                padding-top: 2px;\
                                padding-left: 3px;\
                        }\
                        QPushButton:on {\
                                background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #5AA72D,\
                                stop :   0.5 #B3E296, stop :   0.55 #B3E296, stop :   1.0 #f5f9ff);\
                                padding-top: 2px;\
                                padding-left: 3px;\
                        }\
                        QPushButton:disabled {\
                                background: transparent #e5e9ee;\
                                padding-top: 2px;        \
                                padding-left: 3px;\
                                color: black;\
                        }\
                        ");

}

void KPPPushbutton::paintEvent (QPaintEvent *)
{


    QStyleOptionButton option;
     option.init(this);


     if(isDown()){
        option.state |= QStyle::State_Sunken;
     }
     else{
         // option.state =QStyle::State_Off|QStyle::State_Raised;
     }


     if (isDefault())
         option.features |= QStyleOptionButton::DefaultButton;
     option.text = text();
     option.icon = icon();

     QPainter painter(this);

     style()->drawControl(QStyle::CE_PushButton, &option, &painter, this);

}


void KPPPushbutton::setVisible(bool visible)
{
    if(visible==m_visible) return;
    m_visible=visible;
    //QSize temp=size()


    if(defaultSize==0){
        defaultSize= 400;//parentWidget()->geometry().size().width();
    }
    //bool teste=isHidden();
    int start=0;

    int end=defaultSize;
    animation1 = new QPropertyAnimation(this, "maximumWidth");
    connect(animation1,SIGNAL(finished()),this,SLOT(AnimationFinished()));

    //int factor=abs(defaultSize-maximumWidth());

    animation1->setEasingCurve(QEasingCurve::OutCirc);
    animation1->setStartValue(start);
    animation1->setEndValue(end);
    if(visible){
        animation1->setDuration(300);
        QPushButton::setVisible(visible);
        animation1->setDirection(QAbstractAnimation::Forward);
    }
    else{
        animation1->setDuration(300);
        animation1->setEndValue(width());
        animation1->setDirection(QAbstractAnimation::Backward);
    }


    animation1->start(QAbstractAnimation::DeleteWhenStopped);

 //   QPushButton::setVisible(visible);

}

void KPPPushbutton::AnimationFinished(){
    QPushButton::setVisible(m_visible);
    parentWidget()->update();
}


void KPPPushbutton::enterEvent(QEvent *e)
{
    ishover=true;
    QPushButton::enterEvent(e);
}

void KPPPushbutton::leaveEvent(QEvent *e)
{
    ishover=false;
    QPushButton::leaveEvent(e);
}






void KPPPushbutton::showEvent(QShowEvent *)
{
    if(m_visible){

    }
}
