#include "kppframe.h"
#include "QPropertyAnimation"
#include "QParallelAnimationGroup"

KPPFrame::KPPFrame(QWidget *parent) :
    QFrame(parent),
    m_visible(false),
    m_finalVal(0)
{
     AdjustContents(height(),0);

}

void KPPFrame::SetMaxval(int FinalValue)
{
 m_finalVal=FinalValue;
 //AdjustContents(height(),m_finalVal);

}
bool KPPFrame::visible() const
{
    return m_visible;
}

void KPPFrame::setFrameVisible(bool visible)
{
    m_visible = visible;
    if(m_visible)
        AdjustContents(0,m_finalVal);
    else
        AdjustContents(height(),0);
}


void KPPFrame::AdjustContents(int startValue,int finalValue,QEasingCurve animStyle){



    if (startValue==finalValue) {
        return;
    }
  //  if(finalValue==0)
        animStyle=QEasingCurve::Linear;


    QPropertyAnimation *animation1 = new QPropertyAnimation(this, "maximumHeight");
    animation1->setDuration(300);
    animation1->setStartValue(startValue);
    animation1->setEndValue(finalValue);

    QPropertyAnimation *animation2 = new QPropertyAnimation(this, "minimumHeight");
    animation2->setDuration(300);
    animation2->setStartValue(startValue);
    animation2->setEndValue(finalValue);
    animation2->setEasingCurve(animStyle);

    animation1->setEasingCurve(animStyle);

    //connect(animation1,SIGNAL(finished()),SLOT(AnimationFinished()));

    //animation1->start(QPropertyAnimation::DeleteWhenStopped);



    QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

    animgroup->addAnimation(animation1);
    animgroup->addAnimation(animation2);

    connect(animgroup,SIGNAL(finished()),SLOT(AnimationFinished()));

    animgroup->start(QPropertyAnimation::DeleteWhenStopped);


    //qDebug()<<this->maximumHeight();
}

void KPPFrame::AnimationFinished(){

    parentWidget()->update();

}

void KPPFrame::showEvent(QShowEvent *e)
{
//    if(m_visible)
//        AdjustContents(height(),m_finalVal,QEasingCurve::OutInCubic);
//    else
//        AdjustContents(height(),0);

    QFrame::showEvent(e);
}

void KPPFrame::hideEvent(QHideEvent *e)
{
//    if(m_visible)
//        AdjustContents(height(),m_finalVal,QEasingCurve::OutInCubic);
//    else
//        AdjustContents(height(),0);

     QFrame::hideEvent(e);
}
