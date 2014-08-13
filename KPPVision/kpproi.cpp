#include "kpproi.h"

using namespace Vision;

BOOST_CLASS_EXPORT(ROI);

ROI::ROI(QObject *parent) :
    ResizableItem(parent,0)
{
    m_Name="New ROI";
    m_Scene=0;
    //m_ROIRect = new ResizableItem(this,0);
    //m_ROIRect->setParentItem();

    //m_ROIRect->setPos(500,500);
}
QString ROI::getName() const
{
    return m_Name;
}

void ROI::setName(const QString &Name)
{
    m_Name = Name;
}
QGraphicsScene *ROI::Scene() const
{
    return m_Scene;
}

void ROI::sceneRectChangedSlot(QRectF newrect){
//   QPointF p=m_ROIRect->pos();
//   m_ROIRect->setPos(p);

    if(newrect.width()>boundingRect().width() &&
            newrect.height()>boundingRect().height()){
        setVisible(true);

    }
    else{
        setVisible(false);
    }
}

void ROI::setScene(QGraphicsScene *Scene,QGraphicsItem* parentItem)
{


    if(m_Scene != Scene){
        if(m_Scene!=0)
            disconnect(m_Scene,SIGNAL(sceneRectChanged(QRectF)),this,0);
        m_Scene=Scene;
        if(m_Scene!=0)
            connect(m_Scene,SIGNAL(sceneRectChanged(QRectF)),this,SLOT(sceneRectChangedSlot(QRectF)));
       setParentItem(parentItem);

    }

}


QImage Mat2QImage(IplImage *img)
{

    cv::Mat mat_img=cv::Mat(img,false);

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

void ROI::Process(IplImage *processingImage)
{
    if(processingImage!=0)
        m_ProcessingImage=processingImage;

    roi_x=mapRectToParent(rect()).x();
    roi_y=mapRectToParent(rect()).y();
    roi_w=mapRectToParent(rect()).width();
    roi_h=mapRectToParent(rect()).height();
    CvRect rect2=cvRect(roi_x,roi_y,roi_w,roi_h);

    cvSetImageROI(m_ProcessingImage, rect2);
    cvThreshold(m_ProcessingImage,m_ProcessingImage,100,255,cv::THRESH_BINARY);
    //m_Scene->update(m_Scene->sceneRect());
    QRectF temp=rect();
    //temp.adjust(,2,2,2);
    //parentItem()->update(mapRectToParent(temp));
    parentItem()->update(mapRectToParent(temp));
}






void Vision::ROI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ResizableItem::mousePressEvent(event);
    emit ROIPressed(this);
}
