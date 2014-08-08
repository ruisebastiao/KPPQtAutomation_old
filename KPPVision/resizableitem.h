#ifndef RESIZABLEITEM_H
#define RESIZABLEITEM_H
#include <QtGui>
#include <QGraphicsRectItem>
#include "SizeGripItem.h"
#include "kppvision_global.h"

class KPPVISIONSHARED_EXPORT ResizableItem :public QObject,public QGraphicsRectItem
{
Q_OBJECT
private:
    SizeGripItem* rectSizeGripItem;



public:


    explicit ResizableItem(QObject *parent=0,QGraphicsItem *parentitem = 0);
    bool isselected;


    void Resize(QRectF *NewRect);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //QRectF boundingRect() con
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QVariant itemChange(GraphicsItemChange change,
                                const QVariant &value);


    // QGraphicsItem interface
protected:
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);

    // QGraphicsItem interface
public:
    QPainterPath shape() const;

    // QGraphicsItem interface
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
};

#endif // RESIZABLEITEM_H
