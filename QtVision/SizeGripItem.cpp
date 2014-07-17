/*
 * SizeGripItem - A size grip QGraphicsItem for interactive resizing.
 *
 * Copyright (c) 2011 Cesar L. B. Silveira
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <QBrush>
#include "SizeGripItem.h"
#include <QtGui>
#include <QDebug>


SizeGripItem::HandleItem::HandleItem(int positionFlags, SizeGripItem* parent)
    : QGraphicsRectItem(-2, -2, 4, 4, parent),
      positionFlags_(positionFlags),
      parent_(parent)
{
    setBrush(QBrush(Qt::yellow));
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    //setAcceptsHoverEvents(true);
//    if (positionFlags_ & Center){
//        setRect(-16,-16,32,32);
//       // setFlag(ItemIsMovable,false);
//        //setac
//    }
}

int SizeGripItem::HandleItem::positionFlags() const
{
    return positionFlags_;
}

void SizeGripItem::HandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

        QGraphicsItem::mouseMoveEvent(event);
}

void SizeGripItem::HandleItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    mousehover=false;
 QGraphicsItem::hoverLeaveEvent(event);
}

void SizeGripItem::HandleItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    //if (positionFlags_ & Top)
      //  setCursor(Qt::SizeFDiagCursor);

    mousehover=true;

    //event->accept();
    QGraphicsItem::hoverMoveEvent(event);
}
void SizeGripItem::HandleItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

    return QGraphicsItem::mousePressEvent(event);
}

void SizeGripItem::HandleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
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

QVariant SizeGripItem::HandleItem::itemChange(GraphicsItemChange change,
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


QPointF SizeGripItem::HandleItem::restrictPosition(const QPointF& newPos)
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

SizeGripItem::SizeGripItem(Resizer* resizer, QGraphicsItem* parent)
    : QGraphicsItem(parent),
      resizer_(resizer)
{
    if (parentItem())
        rect_ = parentItem()->boundingRect();

    handleItems_.append(new HandleItem(TopLeft, this));
    handleItems_.append(new HandleItem(Top, this));
    handleItems_.append(new HandleItem(TopRight, this));
    handleItems_.append(new HandleItem(Right, this));
    handleItems_.append(new HandleItem(BottomRight, this));
    handleItems_.append(new HandleItem(Bottom, this));
    handleItems_.append(new HandleItem(BottomLeft, this));
    handleItems_.append(new HandleItem(Left, this));
    handleItems_.append(new HandleItem(Center, this));
    updateHandleItemPositions();
    //setFlag(ItemSendsGeometryChanges);
}

SizeGripItem::~SizeGripItem()
{
    if (resizer_)
        delete resizer_;
}

QRectF SizeGripItem::boundingRect() const
{
    //return QRectF(-rect_.width()/2,-rect_.height()/2);
    return  rect_;
}



void SizeGripItem::paint(QPainter* painter,
                         const QStyleOptionGraphicsItem* option,
                         QWidget* widget)
{

    //auto *itObj = std::find_if(handleItems_.begin(),handleItems_.end(),[](HandleItem o) { return o.positionFlags() == Top; }    );

//    HandleItem selectedobject=*std::find_if(handleItems_.begin(), handleItems_.end(),[] (const HandleItem& s) {  return s.positionFlags() == Top; });

//    if (selectedobject!=0) {

//    }
//    HandleItem *item1=handleItems_.first();
//    HandleItem *item2=handleItems_.last();


//    painter->setPen(QPen(Qt::black, 0, Qt::DashLine));
//    painter->setBrush(QBrush(Qt::black));
    //painter->drawLine(mapRectFromParent(FromToParent(item1->sceneBoundingRect()).center(),mapRectFromParent(item2->boundingRect()).center());

    //rect_.
}

#define IMPL_SET_FN(TYPE, POS)                  \
    void SizeGripItem::set ## POS (TYPE v)      \
    {                                           \
        rect_.set ## POS (v);                   \
        doResize();                             \
    }

IMPL_SET_FN(qreal, Top)
IMPL_SET_FN(qreal, Right)
IMPL_SET_FN(qreal, Bottom)
IMPL_SET_FN(qreal, Left)
IMPL_SET_FN(const QPointF&, TopLeft)
IMPL_SET_FN(const QPointF&, TopRight)
IMPL_SET_FN(const QPointF&, BottomRight)
IMPL_SET_FN(const QPointF&, BottomLeft)


void SizeGripItem::doResize(QRectF *newSize)
{

    if (resizer_)
    {
        if (newSize!=0) {
            rect_=QRectF(newSize->topLeft(),newSize->size());
        }
        (*resizer_)(parentItem(), rect_);
        updateHandleItemPositions();
    }
}



void SizeGripItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
        //event->accept();
        QGraphicsItem::mouseMoveEvent(event);
}

void SizeGripItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event){


    //event->accept();
    QGraphicsItem::hoverMoveEvent(event);
}
void SizeGripItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
   // event->accept();
    return QGraphicsItem::mousePressEvent(event);
}



void SizeGripItem::updateHandleItemPositions()
{
    foreach (HandleItem* item, handleItems_)
    {
        item->setFlag(ItemSendsGeometryChanges, false);

        switch (item->positionFlags())
        {
            case TopLeft:
                item->setPos(rect_.topLeft());
                break;
            case Top:
                item->setPos(rect_.left() + rect_.width() / 2 - 1,
                             rect_.top());
                break;
            case TopRight:
                item->setPos(rect_.topRight());
                break;
            case Right:
                item->setPos(rect_.right(),
                             rect_.top() + rect_.height() / 2 - 1);
                break;
            case BottomRight:
                item->setPos(rect_.bottomRight());
                break;
            case Bottom:
                item->setPos(rect_.left() + rect_.width() / 2 - 1,
                             rect_.bottom());
                break;
            case BottomLeft:
                item->setPos(rect_.bottomLeft());
                break;
            case Left:
                item->setPos(rect_.left(),
                             rect_.top() + rect_.height() / 2 - 1);
                break;
            case Center:
                item->setPos(rect_.topRight().x()+15,rect_.topRight().y()-15);
            break;
        }

        item->setFlag(ItemSendsGeometryChanges, true);
    }
}
