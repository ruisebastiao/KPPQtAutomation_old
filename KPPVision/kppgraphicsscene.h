#ifndef KPPGRAPHICSSCENE_H
#define KPPGRAPHICSSCENE_H

#include "kppvision_global.h"
#include <QGraphicsScene>

class KPPVISIONSHARED_EXPORT KPPGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit KPPGraphicsScene(QObject *parent = 0);

signals:

public slots:


    // QGraphicsScene interface
protected:
    void drawForeground(QPainter *painter, const QRectF &rect);
};

#endif // KPPGRAPHICSSCENE_H
