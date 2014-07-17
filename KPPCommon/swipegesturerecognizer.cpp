#include "swipegesturerecognizer.h"

#include <QMouseEvent>
#include <math.h>
#include <QDebug>

bool
SwipeGestureRecognizer::IsValidMove(int dx, int dy)
{
    // The moved distance is to small to count as not just a glitch.
    if ((qAbs(dx) < MINIMUM_DISTANCE) && (qAbs(dy) < MINIMUM_DISTANCE)) {
        return false;
    }

    return true;
}


// virtual
QGesture*
SwipeGestureRecognizer::create(QObject* pTarget)
{


    QGesture *pGesture = new QSwipeGesture(pTarget);



    return pGesture;


}



// virtual
QGestureRecognizer::Result
SwipeGestureRecognizer::recognize(QGesture* pGesture, QObject *pWatched, QEvent *pEvent)
{


    QGestureRecognizer::Result result = QGestureRecognizer::Ignore;
    QSwipeGesture *pSwipe = static_cast<QSwipeGesture*>(pGesture);




    //qDebug()<<"Watched:"<<pWatched;


    switch(pEvent->type()) {


    case QEvent::MouseButtonPress: {


        QMouseEvent* pMouseEvent = static_cast<QMouseEvent*>(pEvent);
        pSwipe->setProperty("startPoint", pMouseEvent->pos());
        //pGesture->setHotSpot(pMouseEvent->pos());
        result = QGestureRecognizer::MayBeGesture;
        timer.start();
    }
        break;
    case QEvent::MouseMove:{
        QMouseEvent* pMouseEvent = static_cast<QMouseEvent*>(pEvent);
        if(pMouseEvent->buttons() == Qt::LeftButton){

        }

    }
        break;
    case QEvent::MouseButtonDblClick:{
        QMouseEvent* pMouseEvent = static_cast<QMouseEvent*>(pEvent);
        pSwipe->setProperty("startPoint", pMouseEvent->pos());
        return QGestureRecognizer::CancelGesture;
    }
        break;
    case QEvent::MouseButtonRelease: {
        QMouseEvent* pMouseEvent = static_cast<QMouseEvent*>(pEvent);
        const QVariant& propValue = pSwipe->property("startPoint");
        QPointF startPoint = propValue.toPointF();
        QPointF endPoint = pMouseEvent->pos();

        // process distance and direction
        int dx = endPoint.x() - startPoint.x();
        int dy = endPoint.y() - startPoint.y();

        if (!IsValidMove(dx, dy)) {
            // Just a click, so no gesture.
            result = QGestureRecognizer::CancelGesture;

        } else {

            qint64 miliSec = timer.restart();

            if (miliSec > 500)
                return QGestureRecognizer::CancelGesture;

            // Compute the angle.
            qreal angle = ComputeAngle(dx, dy);
            pSwipe->setSwipeAngle(angle);


            result = QGestureRecognizer::FinishGesture;

        }
    }
        break;

    default:
        break;
    }


    return result;
}


void
SwipeGestureRecognizer::reset(QGesture *pGesture)
{
    pGesture->setProperty("startPoint", QVariant(QVariant::Invalid));
    parent::reset(pGesture);
}

qreal
SwipeGestureRecognizer::ComputeAngle(int dx, int dy)
{


    double PI = 3.14159265;

    // Need to convert from screen coordinates direction
    // into classical coordinates direction.
    dy = -dy;

    double result = atan2((double)dy, (double)dx) ;
    result = (result * 180) / PI;

    // Always return positive angle.
    if (result < 0) {
        result += 360;
    }

    return result;
}
