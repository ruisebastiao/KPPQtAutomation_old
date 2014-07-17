#ifndef HANDLEITEM_H
#define HANDLEITEM_H

#include "SizeGripItem.h"

class HandleItem : public QGraphicsRectItem
{
    public:
        HandleItem(int positionFlags, SizeGripItem* parent);
        int positionFlags() const;

    protected:
         void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
         void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
         void mousePressEvent(QGraphicsSceneMouseEvent *event);
         void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

         void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        virtual QVariant itemChange(GraphicsItemChange change,
                                    const QVariant &value);

    private:
        QString myproperty;
        QPointF restrictPosition(const QPointF& newPos);
        bool mousehover;
        int positionFlags_;
        SizeGripItem* parent_;
};


#endif // HANDLEITEM_H
