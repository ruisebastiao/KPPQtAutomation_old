#include "kppanimatedframe.h"
#include "qlayout.h"

KPPAnimatedFrame::KPPAnimatedFrame(QWidget *parent) :
    QFrame(parent)
{


    //set
    animate_opacity = new QPropertyAnimation(this, "windowOpacity", this);
    animate_geometry = new QPropertyAnimation(this, "geometry", this);


    parallel_animations= new QParallelAnimationGroup(this);
    parallel_animations->addAnimation(animate_opacity);
    parallel_animations->addAnimation(animate_geometry);
    animate_geometry->setDuration(50);

    animate_finalgeometry= new QPropertyAnimation(this, "geometry", this);

    animate_finalgeometry->setStartValue(QRect());
    animate_finalgeometry->setEndValue(QRect());
    animate_finalgeometry->setDuration(50);

    animate_geometry->setStartValue(QRect());
    animate_geometry->setEndValue(QRect());

    animate_opacity->setDuration(100);
    animate_opacity->setStartValue(1);
    animate_opacity->setEndValue(1);
    m_visible=false;

    seq_animations=new QSequentialAnimationGroup(this);

    seq_animations->addAnimation(parallel_animations);
    //seq_animations->addPause(10);
    seq_animations->addAnimation(animate_finalgeometry);


    //layout()->setSizeConstraint(QLayout::SetNoConstraint);
    setWindowFlags(Qt::Popup|Qt::FramelessWindowHint);

    connect(seq_animations,SIGNAL(finished()),this,SLOT(AnimationFinished()));

}

KPPAnimatedFrame::~KPPAnimatedFrame()
{

    delete animate_opacity ;
    delete animate_geometry;
    delete parallel_animations;
}
QRect KPPAnimatedFrame::AlignmentRect() const
{
    return m_alignmentRect;
}

void KPPAnimatedFrame::setAlignmentRect(const QRect &alignmentRect)
{

    m_alignmentRect = alignmentRect;
    QRect geo_start=geometry();



    geo_start.setTopLeft(m_alignmentRect.topLeft());
    geo_start.setBottomRight(m_alignmentRect.bottomRight());
    geo_start.setLeft(m_alignmentRect.left()+m_alignmentRect.width()+5);
    geo_start.setWidth(0);

    int temp1=height();
    int temp2=m_alignmentRect.height();
    int final_height_diff=abs(temp1-temp2);

    setGeometry(geo_start);

    QRect geo_end=QRect(geo_start.topLeft(),geo_start.bottomRight());
    geo_end.setWidth(250);

    animate_geometry->setStartValue(geo_start);
    animate_geometry->setEndValue(geo_end);

    animate_finalgeometry->setStartValue(geo_end);

    QRect geo_final=QRect(geo_end.topLeft(),geo_end.bottomRight());
    geo_final.setHeight(geo_final.height()+150);
    animate_finalgeometry->setEndValue(geo_final);
}



void KPPAnimatedFrame::setVisible(bool visible)
{


    m_visible=visible;

    if(visible){

        //        animate_opacity->setDirection(QPropertyAnimation::Forward);
        //        animate_geometry->setDirection(QPropertyAnimation::Forward);
        //        parallel_animations->setDirection(QPropertyAnimation::Forward);
        seq_animations->setDirection(QPropertyAnimation::Forward);
        this->move(m_alignmentRect.x()+m_alignmentRect.size().width()+5,m_alignmentRect.y());//,width(),height());
        QWidget::setVisible(m_visible);
    }
    else{
        //animate_opacity->setDuration(1500);
        this->setWindowOpacity(1);
        //        animate_opacity->setDirection(QPropertyAnimation::Backward);
        //        animate_geometry->setDirection(QPropertyAnimation::Backward);

        //        parallel_animations->setDirection(QPropertyAnimation::Backward);
        seq_animations->setDirection(QPropertyAnimation::Backward);
    }


    seq_animations->start();


}

void KPPAnimatedFrame::AnimationFinished(){
    QWidget::setVisible(m_visible);
}


void KPPAnimatedFrame::leaveEvent(QEvent *e)
{
    QFrame::leaveEvent(e);
}

void KPPAnimatedFrame::focusInEvent(QFocusEvent *e)
{
    QFrame::focusInEvent(e);
}

void KPPAnimatedFrame::focusOutEvent(QFocusEvent *e)
{
    QFrame::focusOutEvent(e);

}


void KPPAnimatedFrame::hideEvent(QHideEvent *e)
{
    QFrame::hideEvent(e);
    if(parentWidget()!=0){
        parentWidget()->update();
    }
}
