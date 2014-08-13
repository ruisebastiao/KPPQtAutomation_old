#include "imageholder.h"
#include "qpainter.h";
#include "qdebug.h"
#include "QStyleOptionGraphicsItem"
#include "kppvisionauxfunctions.h"

using namespace cv;
using namespace Vision;


ImageHolder::ImageHolder(QGraphicsItem *parent,IplImage* image) :
    QGraphicsItem (parent)
{

   // InImage=0;
    setCacheMode(QGraphicsItem::ItemCoordinateCache);
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption,true);
}
Mat ImageHolder::Image() const
{
    return m_Image;
}

void ImageHolder::setImage(Mat Image)
{
   // m_Image = Image;
//    if(InImage!=0)
//        delete InImage;
    InImage= cvMat2QImage(Image);

}



QRectF ImageHolder::boundingRect() const
{

    if(!InImage.size().isEmpty()){
        return QRectF(0,0,InImage.width(),InImage.height());
    }

    return QRectF(0,0,0,0);
}

void ImageHolder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   // QGraphicsItem::paint(painter,option,widget);
    if(!InImage.size().isEmpty()){
        QRectF temp=option->exposedRect;
        temp.adjust(-10,-10,10,10);
        painter->setClipRect(temp);

        painter->drawImage(0,0,InImage);
    }

}
