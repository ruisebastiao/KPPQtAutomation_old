#ifndef SWIPEGESTURERECOGNIZER_H
#define SWIPEGESTURERECOGNIZER_H

#include "kppcommon_global.h"

#include <QObject>

#include <QGestureRecognizer>
#include <QGesture>
#include <QElapsedTimer>
#include <QGestureEvent>

class KPPCOMMONSHARED_EXPORT SwipeGestureRecognizer : public QGestureRecognizer
{

public:
    QGestureRecognizer::Result recognize(QGesture* pGesture, QObject *pWatched, QEvent *pEvent);
private:
   static const int MINIMUM_DISTANCE = 30;

   typedef QGestureRecognizer parent;

   bool IsValidMove(int dx, int dy);

   qreal ComputeAngle(int dx, int dy);

   virtual QGesture* create(QObject* pTarget);



   void reset (QGesture *pGesture);

   //A timer to make sure we don't get double events. It's a small hack to prevent an android/emulator bug.
     QElapsedTimer timer;
};




#endif // SWIPEGESTURERECOGNIZER_H
