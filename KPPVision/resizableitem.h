#ifndef RESIZABLEITEM_H
#define RESIZABLEITEM_H
#include <QtGui>
#include <QGraphicsRectItem>
#include "SizeGripItem.h"
#include "icxmlserializable.h"

class ResizableItem : public icXmlSerializable,public QGraphicsRectItem
{
Q_OBJECT
private:
    SizeGripItem* rectSizeGripItem;
    //QString m_name;
    virtual bool serialize();

    virtual bool deserialize();

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

};

#endif // RESIZABLEITEM_H
