#include "resizableitem.h"

#include <QDebug>
#include <QtGui>

namespace
{
class KPPVISIONSHARED_EXPORT RectResizer : public SizeGripItem::Resizer
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

class KPPVISIONSHARED_EXPORT EllipseResizer : public SizeGripItem::Resizer
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




//template<class Archive>
// void ResizableItem::save(Archive & ar, const unsigned int version) {


//    qreal x=mapRectToParent(this->rect()).x();
//    ar << make_nvp("X", x);
//}

//template<class Archive>
// void ResizableItem::load(Archive & ar, const unsigned int version)
//{
//    qreal x;
//    ar >> make_nvp("X",x);
//    QRectF newrect=rect();
//    newrect.setX(x);
//    this->setRect(newrect);
//}


//    template<class Archive>
//void ResizableItem::serialize(Archive &ar, const unsigned int file_version)
//    {
//        //ar & boost::serialization::make_nvp("Rect", m_rect);
//        m_rect=this->rect();

//      //  boost::serialization::split_free(ar,file_version);
//      //  setRect(m_rect);
////        qDebug()<<"rect:"<<mapRectToParent(m_rect);
//    }

ResizableItem::ResizableItem(QObject *parent, QGraphicsItem *parentitem):
    QGraphicsRectItem(-50,-50,100,100,parentitem)
{



   //qDebug()<<
        //teste.readRawData()
    //    temp.adjust(-5,-5,5,5);
    //    bound(temp);
    //setRect(-50,-50,100,100);
    //this->setOffset( -0.5 * QPointF( boundingRect().width(), boundingRect().height() ));
    QPen blackpen(Qt::black);
    blackpen.setWidth(1);
    QBrush transparentbrush(Qt::transparent);
    //rectitem = new ResizableItem(0,0,100,100);


    setAcceptTouchEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    //setFlag(ItemSendsGeometryChanges, true);
    //setFlag(ItemIgnoresTransformations);
    setBrush(transparentbrush);
    setPen(blackpen);
    setAcceptHoverEvents(true);

    isselected=false;
    rectSizeGripItem =
            new SizeGripItem(new RectResizer, this);

    Resize(&boundingRect());



}
void ResizableItem::Resize(QRectF *NewRect){
    rectSizeGripItem->doResize(NewRect);
    //setRect(0,0,500,500);
}

void ResizableItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){

    if(isSelected()){
    //if(isselected){
        painter->setPen(QPen(Qt::red, 1, Qt::DashLine));
        QRectF bound=QRectF(boundingRect());
        //bound.adjust(-2,-2,2,2);
        painter->drawRect(bound);
    }
    //   else{
    // # Paint rectangle
    painter->setPen(QPen(Qt::yellow, 1, Qt::SolidLine));

    painter->drawRect(rect());
    //  }

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

        //qDebug()<<parent();

        if(parentItem()){


            if (newrect.left()<-2 || newrect.right()>parentItem()->boundingRect().width()+2) {

                newpos.setX(pos().x());

            }

            if (newrect.top()<-2 || newrect.bottom()>parentItem()->boundingRect().height()+2) {

                newpos.setY(pos().y());

            }

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
    QGraphicsItem::mousePressEvent(event);


}


void ResizableItem::focusInEvent(QFocusEvent *event)
{
    //isele
    setZValue(1000);
    isselected=true;
//    setSelected(true);
//    update();
    QGraphicsItem::focusInEvent(event);

}

void ResizableItem::focusOutEvent(QFocusEvent *event)
{
    setZValue(0);
    isselected=false;
    update();
    QGraphicsItem::focusOutEvent(event);
}


QPainterPath ResizableItem::shape() const
{
    //    //QPainterPathStroker p2;

    //    ////p2.setWidth();

    //    QPainterPath path;
    //    QRectF bound=QRectF(boundingRect());
    //    bound.adjust(20,20,-20,-20);
    //      path.addRect(bound);

    //    //  return p2.createStroke(path);
    //      return path;

    return QGraphicsItem::shape();
}


void ResizableItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event);
}


QRectF ResizableItem::boundingRect() const
{
    QRectF temp=rect();
    temp.adjust(-3,-3,3,3);
    return temp;

}


bool ResizableItem::sceneEvent(QEvent *event)
{
    return QGraphicsItem::sceneEvent(event);
}



