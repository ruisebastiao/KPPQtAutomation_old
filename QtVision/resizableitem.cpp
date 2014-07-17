#include "resizableitem.h"
#include <QDebug>
#include <QtGui>

namespace
{
    class RectResizer : public SizeGripItem::Resizer
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsRectItem* rectItem =
                    dynamic_cast<QGraphicsRectItem*>(item);

                if (rectItem)
                {
                    rectItem->setRect(rect);
                }
            }
    };

    class EllipseResizer : public SizeGripItem::Resizer
    {
        public:
            virtual void operator()(QGraphicsItem* item, const QRectF& rect)
            {
                QGraphicsEllipseItem* ellipseItem =
                    dynamic_cast<QGraphicsEllipseItem*>(item);

                if (ellipseItem)
                {
                    ellipseItem->setRect(rect);
                }
            }
    };
}

bool ResizableItem::serialize()
{
    setSerialProperty("x", rect().x());
    setSerialProperty("y", rect().y());
    setSerialProperty("w", rect().width());
    setSerialProperty("h", rect().height());
    return true;
}

bool ResizableItem::deserialize()
{
     QRectF *newrect=new QRectF();
     newrect->setX(getSerialProperty("x").toReal());
     newrect->setY(getSerialProperty("y").toReal());
     newrect->setWidth(getSerialProperty("w").toReal());
     newrect->setHeight(getSerialProperty("h").toReal());
     //rectSizeGripItem->doResize(newrect);
    return true;
}

ResizableItem::ResizableItem(QObject *parent, QGraphicsItem *parentitem)
    :icXmlSerializable(parent,"ROIRect"),
    QGraphicsRectItem(-50,-50,100,100,parentitem)
{
    //setRect(-50,-50,100,100);
    //this->setOffset( -0.5 * QPointF( boundingRect().width(), boundingRect().height() ));
    QPen blackpen(Qt::black);
    blackpen.setWidth(2);
    QBrush transparentbrush(Qt::transparent);
    //rectitem = new ResizableItem(0,0,100,100);

    setAcceptTouchEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

    //setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //setFlag(ItemSendsGeometryChanges, true);
    //setFlag(ItemIgnoresTransformations);
    setBrush(transparentbrush);
    setPen(blackpen);
    setAcceptHoverEvents(true);


    rectSizeGripItem =
              new SizeGripItem(new RectResizer, this);


}
void ResizableItem::Resize(QRectF *NewRect){
      rectSizeGripItem->doResize(NewRect);
    //setRect(0,0,500,500);
}

void ResizableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    if(isselected){
       painter->setPen(QPen(Qt::red, 0, Qt::DashLine));
       QRectF bound=QRectF(boundingRect());
       bound.adjust(-1,-1,1,1);
       painter->drawRect(bound);
    }
      // # Paint rectangle
       painter->setPen(QPen(Qt::black, 0, Qt::SolidLine));
       painter->drawRect(rect());

//      // # If mouse is over, draw handles
//       if self.mouseOver:
//           # if rect selected, fill in handles
//           if self.isSelected():
//               painter.setBrush(QtGui.QBrush(QtGui.QColor(0,0,0)))
//           painter.drawRect(self.topLeft)
//           painter.drawRect(self.topRight)
//           painter.drawRect(self.bottomLeft)
//           painter.drawRect(self.bottomRight)

}

QVariant ResizableItem::itemChange(GraphicsItemChange change,
                            const QVariant &value){


    if (change == ItemPositionChange) {

        QPointF oldpos=scenePos();
        QPointF newpos=value.toPointF();

        QPointF diff=newpos-oldpos;

        QRectF newrect=QRectF(sceneBoundingRect().translated(diff));


        if (newrect.left()<-2 || newrect.right()>parentItem()->boundingRect().width()+2) {

            newpos.setX(pos().x());

        }

        if (newrect.top()<-2 || newrect.bottom()>parentItem()->boundingRect().height()+2) {

            newpos.setY(pos().y());

        }

        return newpos;

    }


    return QGraphicsItem::itemChange(change,value);
}



void ResizableItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){


QGraphicsItem::mouseMoveEvent(event);

}

void ResizableItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){

    QGraphicsItem::mouseReleaseEvent(event);
}

void ResizableItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

    isselected=true;
    update();
    QGraphicsItem::mousePressEvent(event);
}
