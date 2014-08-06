#include "kppanimatedframe.h"
#include "ui_kppanimatedframe.h"


KPPAnimatedFrame::KPPAnimatedFrame(QWidget *parent, Qt::WindowFlags f, QRect alignmentRect) :
    QFrame(parent,f),
    ui(new Ui::KPPAnimatedFrame)
{
    ui->setupUi(this);
     setWindowModality(Qt::NonModal);
     m_alignmentRect=alignmentRect;
     //set
     animate_opacity = new QPropertyAnimation(this, "windowOpacity", this);
     animate_width = new QPropertyAnimation(this, "size", this);
     animation= new QParallelAnimationGroup(this);
     animation->addAnimation(animate_opacity);
     animation->addAnimation(animate_width);
     animate_width->setDuration(150);
     animate_width->setStartValue(QSize(0,m_alignmentRect.height()));

     animate_width->setEndValue(QSize(250,m_alignmentRect.height()));

     animate_opacity->setDuration(150);
     animate_opacity->setStartValue(0);
     animate_opacity->setEndValue(1);
     m_visible=false;

     connect(animation,SIGNAL(finished()),this,SLOT(AnimationFinished()));

}

KPPAnimatedFrame::~KPPAnimatedFrame()
{
    delete ui;
    delete animate_opacity ;
    delete animate_width;
    delete animation;
}


void KPPAnimatedFrame::setVisible(bool visible)
{


    m_visible=visible;

    if(visible){
      //  this->setWindowOpacity(0);

//        QPoint align_pt=m_alignmentRect->mapToGlobal(QPoint(0,0));
//        QPoint align_pt2=mapFromGlobal(align_pt);


        animate_opacity->setDirection(QPropertyAnimation::Forward);
        animate_width->setDirection(QPropertyAnimation::Forward);
        animation->setDirection(QPropertyAnimation::Forward);
        QRect r=geometry();
        r.setWidth(0);

       // animate_opacity->setDuration(250);
        setGeometry(r);
        this->updateGeometry();

        this->move(m_alignmentRect.x()+m_alignmentRect.size().width()+5,m_alignmentRect.y());//,width(),height());
        QWidget::setVisible(m_visible);
    }
    else{
        //animate_opacity->setDuration(1500);
        animate_opacity->setDirection(QPropertyAnimation::Backward);
        animate_width->setDirection(QPropertyAnimation::Backward);
        this->setWindowOpacity(1);
        animation->setDirection(QPropertyAnimation::Backward);
    }


   animation->start();


}

void KPPAnimatedFrame::AnimationFinished(){
    QWidget::setVisible(m_visible);
}


void KPPAnimatedFrame::leaveEvent(QEvent *e)
{
    QWidget::leaveEvent(e);
}

void KPPAnimatedFrame::focusInEvent(QFocusEvent *e)
{
     QWidget::focusInEvent(e);
}

void KPPAnimatedFrame::focusOutEvent(QFocusEvent *e)
{
        QWidget::focusOutEvent(e);

}
