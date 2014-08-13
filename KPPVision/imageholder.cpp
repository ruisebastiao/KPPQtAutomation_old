#include "imageholder.h"
#include "qpainter.h";
#include "qdebug.h"
#include "QStyleOptionGraphicsItem"
//using namespace Vision;


static QImage IplImage2QImage(IplImage *iplImage)
{

    cv::Mat mat_img(iplImage);

    switch ( mat_img.type() )
        {
    // 8-bit, 4 channel
            case CV_8UC4:
            {
               QImage image( mat_img.data, mat_img.cols, mat_img.rows, mat_img.step, QImage::Format_RGB32 );

               return image;
            }

            // 8-bit, 3 channel
            case CV_8UC3:
            {
               QImage image( mat_img.data, mat_img.cols, mat_img.rows, mat_img.step, QImage::Format_RGB888 );

               return image.rgbSwapped();
            }

            // 8-bit, 1 channel
            case CV_8UC1:
            {
               static QVector<QRgb>  sColorTable;

               // only create our color table once
               if ( sColorTable.isEmpty() )
               {
                  for ( int i = 0; i < 256; ++i )
                     sColorTable.push_back( qRgb( i, i, i ) );
               }

               QImage image( mat_img.data, mat_img.cols, mat_img.rows, mat_img.step, QImage::Format_Indexed8 );

               image.setColorTable( sColorTable );

               return image;
            }

            default:
               qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << mat_img.type();
               break;
         }

         return QImage();
}

ImageHolder::ImageHolder(QGraphicsItem *parent,IplImage* image) :
    QGraphicsItem (parent)
{
    m_Image=0;
    InImage=0;
    setCacheMode(QGraphicsItem::ItemCoordinateCache);
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption,true);
}
IplImage *ImageHolder::Image() const
{
    return m_Image;
}

void ImageHolder::setImage(IplImage *Image)
{
    m_Image = Image;
    if(InImage!=0)
        delete InImage;
    InImage= new QImage(IplImage2QImage(Image));

}



QRectF ImageHolder::boundingRect() const
{

    if(m_Image!=0){
        return QRectF(0,0,m_Image->width,m_Image->height);
    }

    return QRectF();
}

void ImageHolder::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
   // QGraphicsItem::paint(painter,option,widget);
    if(m_Image!=0){
        QRectF temp=option->exposedRect;
        temp.adjust(-10,-10,10,10);
        painter->setClipRect(temp);

        painter->drawImage(0,0,*InImage);
    }

}
