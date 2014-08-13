#include "kpproi.h"

using namespace Vision;
using namespace cv;

BOOST_CLASS_EXPORT(ROI);

ROI::ROI(QObject *parent) :
    ResizableItem(parent,0)
{
    m_Name="New ROI";
    m_Scene=0;
    setVisible(false);
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


void ROI::Process()
{
    Process(Mat());
}

void ROI::Process(Mat processingImage)
{
    if(!processingImage.empty())
        m_ProcessingImage=processingImage;

    roi_x=mapRectToParent(rect()).x();
    roi_y=mapRectToParent(rect()).y();
    roi_w=mapRectToParent(rect()).width();
    roi_h=mapRectToParent(rect()).height();
    Rect rect2=Rect(roi_x,roi_y,roi_w,roi_h);

    Mat roiImage=m_ProcessingImage(rect2);
    Mat roiImagegray;
    cvtColor(roiImage,roiImagegray,CV_BGR2GRAY);

    threshold(roiImagegray,roiImagegray,100,255,cv::THRESH_BINARY);

    cv::vector<Mat> channels;
    channels.push_back(roiImagegray);
    channels.push_back(roiImagegray);
    channels.push_back(roiImagegray);

    merge(channels,roiImage);
     QRectF temp=rect();
    //temp.adjust(,2,2,2);
    parentItem()->update(parentItem()->boundingRect());
    //parentItem()->update(mapRectToParent(temp));
}






void Vision::ROI::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ResizableItem::mousePressEvent(event);
    emit ROIPressed(this);
}
