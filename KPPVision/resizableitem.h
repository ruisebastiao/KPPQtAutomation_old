#ifndef RESIZABLEITEM_H
#define RESIZABLEITEM_H
#include <QtGui>
#include <QGraphicsRectItem>
#include "SizeGripItem.h"
#include "kppvision_global.h"
#include "BoostDef.h"
#include "QPointF"

class KPPVISIONSHARED_EXPORT ResizableItem :public QObject,public QGraphicsRectItem
{
    Q_OBJECT


 //

private:
    SizeGripItem* rectSizeGripItem;



public:


    explicit ResizableItem(QObject *parent=0,QGraphicsItem *parentitem = 0);
    bool isselected;


    friend std::ostream & operator<<(std::ostream &os, const ResizableItem &req);

    void Resize(QRectF *NewRect);

//    template<typename Archive>
//    void serialize(Archive & ar, const unsigned int file_version);





private:
    QRectF m_rect;

    friend class boost::serialization::access;



     //BOOST_SERIALIZATION_SPLIT_MEMBER()

    template<class Archive>
    void serialize(
        Archive & ar,
        const unsigned int file_version
    ){
        boost::serialization::split_member(ar, *this, file_version);
    }


    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
         QRectF mapped=mapRectToParent(this->rect());
         qreal x,y,width,height;
         x=mapped.topLeft().x();
         y=mapped.topLeft().y();
         width=mapped.width();
         height=mapped.height();

         ar << boost::serialization::make_nvp("X",x);
         ar << boost::serialization::make_nvp("Y",y);
         ar << boost::serialization::make_nvp("W",width);
         ar << boost::serialization::make_nvp("H",height);

    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        qreal x,y,width,height;

        ar >> boost::serialization::make_nvp("X",x);
        ar >> boost::serialization::make_nvp("Y",y);
        ar >> boost::serialization::make_nvp("W",width);
        ar >> boost::serialization::make_nvp("H",height);

        QRectF newrect=QRectF(x,y,width,height);
        this->setRect(mapRectFromParent(newrect));
        Resize(&boundingRect());
    }




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

    // QGraphicsItem interface
protected:
    bool sceneEvent(QEvent *event);

signals:
    void teste();
};

//BOOST_SERIALIZATION_SPLIT_FREE(ResizableItem)


#endif // RESIZABLEITEM_H
