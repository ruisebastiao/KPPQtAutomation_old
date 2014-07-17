#include "handleitem.h"


HandleItem::HandleItem(int positionFlags, SizeGripItem* parent)
    : QGraphicsRectItem(-4, -4, 8, 8, parent),
      positionFlags_(positionFlags),
      parent_(parent)
{
    setBrush(QBrush(Qt::yellow));
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);

}

int HandleItem::positionFlags() const
{
    return positionFlags_;
}

void HandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

        QGraphicsItem::mouseMoveEvent(event);
}

void HandleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    mousehover=false;
 QGraphicsItem::hoverLeaveEvent(event);
}

void HandleItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    //if (positionFlags_ & Top)
      //  setCursor(Qt::SizeFDiagCursor);

    mousehover=true;

    //event->accept();
    QGraphicsItem::hoverMoveEvent(event);
}
void HandleItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

    return QGraphicsItem::mousePressEvent(event);
}

void HandleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    if(mousehover){

            painter->setPen(QPen(Qt::black, 0, Qt::DashLine));
            painter->setBrush(QBrush(Qt::green));
            painter->drawRect(rect());

    }
    else{

        painter->setPen(QPen(Qt::black, 0, Qt::SolidLine));
        painter->setBrush(QBrush(Qt::yellow));
        painter->drawRect(rect());

    }



}

QVariant HandleItem::itemChange(GraphicsItemChange change,
                                              const QVariant &value)
{
    QVariant retVal = value;



    if (change == ItemPositionChange)
    {
        retVal = restrictPosition(value.toPointF());


    }
    else if (change == ItemPositionHasChanged)
    {

        QPointF pos = value.toPointF();
      //  qDebug()<<"Pos:"<<pos;

        switch (positionFlags_)
        {
            case TopLeft:
                parent_->setTopLeft(pos);
                break;
            case Top:
                parent_->setTop(pos.y());
                break;
            case TopRight:
                parent_->setTopRight(pos);
                break;
            case Right:
                parent_->setRight(pos.x());
                break;
            case BottomRight:

                parent_->setBottomRight(pos);
                break;
            case Bottom:
                parent_->setBottom(pos.y());
                break;
            case BottomLeft:
                parent_->setBottomLeft(pos);
                break;
            case Left:
                parent_->setLeft(pos.x());
                break;
            case Center:
                parent_->setPos(pos);
            break;
        }
    }
//    qDebug()<<"change:"<<mapToScene(parent_->pos());
//    if (mapToScene(parent_->pos()).x()<0) {
//        //QGraphicsItem::itemChange( change, value );

//    }

    return QGraphicsItem::itemChange( change, retVal );
//    return retVal;
}


QPointF HandleItem::restrictPosition(const QPointF& newPos)
{
    QPointF retVal = pos();
    QPointF mapped=parent_->mapToScene(newPos);

    QRectF parentGraphicItemRect=parent_->parentItem()->parentItem()->boundingRect();
//    qDebug()<<"Pos:"<<mapped.x();
//    qDebug()<<"Size:"<<parentGraphicItemRect.width();



    if (positionFlags_ & Top || positionFlags_ & Bottom)
        retVal.setY(newPos.y());

    if (positionFlags_ & Left || positionFlags_ & Right)
        retVal.setX(newPos.x());

    if (positionFlags_ & Top && retVal.y() > parent_->rect_.bottom())
        retVal.setY(parent_->rect_.bottom());
    else if (positionFlags_ & Bottom && retVal.y() < parent_->rect_.top())
        retVal.setY(parent_->rect_.top());

    if (positionFlags_ & Left && retVal.x() > parent_->rect_.right())
        retVal.setX(parent_->rect_.right());
    else if (positionFlags_ & Right && retVal.x() < parent_->rect_.left())
        retVal.setX(parent_->rect_.left());

    if (mapped.x()<-2) {
        retVal.setX(pos().x());
    }

    if (mapped.y()<-2) {
        retVal.setY(pos().y());
    }
    if (mapped.x()>parentGraphicItemRect.width()) {
        retVal.setX(pos().x());
    }

    if (mapped.y()>parentGraphicItemRect.height()) {
        retVal.setY(pos().y());
    }

    return retVal;
}
