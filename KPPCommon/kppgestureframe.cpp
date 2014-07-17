#include "kppgestureframe.h"

KPPGestureFrame::KPPGestureFrame(QWidget *parent) :
    QFrame(parent)
{
    grabGesture(Qt::SwipeGesture);
}


//bool KPPGestureFrame::event(QEvent *pEvent)
//{

//            switch (pEvent->type()) {
//                case QEvent::Gesture:
//                    std::cout << "Gesture Event Received from event()" << std::endl;
//            }

//            return QFrame::event(pEvent);

//}
