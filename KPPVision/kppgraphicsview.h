#ifndef KPPGRAPHICSVIEW_H
#define KPPGRAPHICSVIEW_H

#include "kppvision_global.h"
#include <QGraphicsView>

class KPPVISIONSHARED_EXPORT KPPGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit KPPGraphicsView(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *);
};

#endif // KPPGRAPHICSVIEW_H
