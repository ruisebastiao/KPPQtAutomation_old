#ifndef SLIDINGSTACKEDWIDGET_H
#define SLIDINGSTACKEDWIDGET_H

#include <QStackedWidget>

#include <QtGui>
#include <QWidget>
#include <QDebug>
#include <QEasingCurve>
#include "swipegesturerecognizer.h"
/*!
Description
        SlidingStackedWidget is a class that is derived from QtStackedWidget
        and allows smooth side shifting of widgets, in addition
        to the original hard switching from one to another as offered by
        QStackedWidget itself.
*/

class KPPCOMMONSHARED_EXPORT SlidingStackedWidget : public QStackedWidget
{
        Q_OBJECT

public:
        //! This enumeration is used to define the animation direction
        enum t_direction {
                LEFT2RIGHT,
                RIGHT2LEFT,
                TOP2BOTTOM,
                BOTTOM2TOP,
                AUTOMATIC
        };


        enum t_SwipeDirection
          {
             SwLeft,
             SwRight
          };


        //! The Constructor and Destructor
        SlidingStackedWidget(QWidget *parent=0);
        ~SlidingStackedWidget(void);


public slots:
        //! Some basic settings API
        void setSpeed(int speed);   //animation duration in milliseconds
        void setAnimation(enum QEasingCurve::Type animationtype); //check out the QEasingCurve documentation for different styles
        void setVerticalMode(bool vertical=true);
        void setWrap(bool wrap);    //wrapping is related to slideInNext/Prev;it defines the behaviour when reaching last/first page

        //! The Animation / Page Change API
        void slideInNext(int next=-1);
        void slideInPrev(int next);
        void slideIn(SlidingStackedWidget::t_SwipeDirection SwipeDirection);
        void slideInIdx(int idx, enum t_direction direction=AUTOMATIC);


signals:
        //! this is used for internal purposes in the class engine
        void animationFinished(void);

protected slots:
        //! this is used for internal purposes in the class engine
        void animationDoneSlot(void);

protected:
        //! this is used for internal purposes in the class engine
        void slideInWgt(QWidget * widget, enum t_direction direction=AUTOMATIC);

        QWidget *m_mainwindow;

        int m_speed;
        enum QEasingCurve::Type m_animationtype;
        bool m_vertical;
        int m_now;
        int m_next;
        bool m_wrap;
        QPoint m_pnow;
        bool m_active;

        QList<QWidget*> blockedPageList;
       // bool event(QEvent *event);
        //void childEvent(QChildEvent *event);
        //bool eventFilter(QObject *, QEvent *);        
        bool event(QEvent *event);

private:
        bool gestureEvent(QGestureEvent *event);
        //bool OnGestureEvent(QGestureEvent* pEvent);
        //bool OnSwipeGesture(QSwipeGesture* pSwipe);


        bool swipeTriggered(QSwipeGesture *pSwipe);
};














#endif // SLIDINGSTACKEDWIDGET_H
