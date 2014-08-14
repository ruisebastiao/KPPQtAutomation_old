#ifndef KPPGRAPHICSVIEW_H
#define KPPGRAPHICSVIEW_H

#include "kppvision_global.h"
#include <QGraphicsView>
#include "qscroller.h"

class KPPVISIONSHARED_EXPORT KPPGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit KPPGraphicsView(QWidget *parent = 0);

private:
     int _numScheduledScalings;
     bool ignoreScale;

     QPointF pointBeforeScale;
     QPointF screenCenter;
     qreal zoomScale() const;
     void setZoomScale(qreal scale);
     qreal scaleMin,scaleMax;
     QScroller *scroller;

signals:

public slots:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *);
private slots:
    void scalingTime(qreal x);
    void animFinished();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *);

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *);
};

#endif // KPPGRAPHICSVIEW_H
