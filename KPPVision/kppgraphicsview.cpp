#include "kppgraphicsview.h"
#include "QPaintEvent"
#include "QGraphicsItemGroup"
#include "qtimeline.h"
#include "qdebug.h"


KPPGraphicsView::KPPGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setInteractive(true);

    //this->rubberBandRect()
    //scene()->items().at(0)->
    _numScheduledScalings=0;

    scaleMin=-20;
    scaleMax=20;

    scroller = QScroller::scroller(this);
    QScrollerProperties props=scroller->scrollerProperties();

    QVariant overshootPolicy = QVariant::fromValue<QScrollerProperties::OvershootPolicy>(QScrollerProperties::OvershootAlwaysOff);
    props.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy, overshootPolicy);
    props.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy, overshootPolicy);

    //QVariant lockaxisthresh = QVariant::fromValue<qreal>(0.2);

    //props.setScrollMetric(QScrollerProperties::AxisLockThreshold, lockaxisthresh);

    scroller->setScrollerProperties(props);

}



void KPPGraphicsView::paintEvent(QPaintEvent *e)
{

    QGraphicsView::paintEvent(e);

    //    QPainter painter(viewport());

    //    if(scene()->selectedItems().count()>1){
    //        QGraphicsItemGroup* group= scene()->selectedItems().at(0)->group();
    //        if(group!=0){
    //            painter.drawRect(group->boundingRect());
    //        }
    //        ////         group->se
    //        //        //scene()->selectedItems()
    //        //     }
    //    }
    //    //     //painter.draw


}

void KPPGraphicsView::animFinished()
{
    if (_numScheduledScalings > 0)
        _numScheduledScalings--;
    else
        _numScheduledScalings++;


    sender()->~QObject();
}

//! Returns the current zoom scale.
qreal KPPGraphicsView::zoomScale() const
{
    return transform().m11();
}


/// Sets the current zoom scale.
void KPPGraphicsView::setZoomScale(qreal scale)
{
    qreal s = qMax(scaleMin, qMin(scaleMax, scale));
    setTransform(QTransform::fromScale(s, s));
}

void KPPGraphicsView::scalingTime(qreal x)
{
    qreal factor = 1.0 + qreal(_numScheduledScalings) / 300.0;

    QTransform t=transform();
    t.scale(factor,factor);
    QRectF temp=t.mapRect(scene()->itemsBoundingRect());
    QRect temp2=rect();
//    qDebug()<<rect();
//    qDebug()<<temp;

    if((temp.width()< rect().width()-5) && factor<1){
        ignoreScale=true;
        //_numScheduledScalings=0;
        return;
    }

    scale(factor, factor);
}

void KPPGraphicsView::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers().testFlag(Qt::ControlModifier))
    {
        ignoreScale=false;
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15;  // see QWheelEvent documentation
        _numScheduledScalings += numSteps;
        if (_numScheduledScalings * numSteps < 0)  // if user moved the wheel in another direction, we reset previously scheduled scalings
            _numScheduledScalings = numSteps;


        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);




        QTimeLine *anim = new QTimeLine(350, this);
        anim->setUpdateInterval(20);

        connect(anim, SIGNAL(valueChanged(qreal)), SLOT(scalingTime(qreal)));
        connect(anim, SIGNAL(finished()), SLOT(animFinished()));
        anim->start();
        return;
    }
    QGraphicsView::wheelEvent(event);

}


void KPPGraphicsView::mousePressEvent(QMouseEvent *event)
{



    if(event->modifiers().testFlag(Qt::ShiftModifier)){
        setDragMode(QGraphicsView::RubberBandDrag);
    }
    else if(event->modifiers().testFlag(Qt::ControlModifier)){





    }
    else{



    }
    QGraphicsView::mousePressEvent(event);
}


void KPPGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
     QGraphicsView::mouseReleaseEvent(event);
     setDragMode(NoDrag);
}


void KPPGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control){

         scroller->grabGesture(this, QScroller::LeftMouseButtonGesture);

    }
    QGraphicsView::keyPressEvent(event);
}

void KPPGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Control){
        scroller->stop();
         scroller->ungrabGesture(this);

    }

    QGraphicsView::keyReleaseEvent(event);
}


void KPPGraphicsView::mouseMoveEvent(QMouseEvent *event)
{

     QGraphicsView::mouseMoveEvent(event);

//     QPointF delta = target_viewport_pos - mouse_event->pos();
//         if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5) {
//           target_viewport_pos = event->pos();
//           viewport()-> = mapToScene(event->pos());
//         }

}
