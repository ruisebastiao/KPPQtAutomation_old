#include "kpproi.h"

using namespace Vision;

ROI::ROI(QObject *parent) :
    QObject(parent)
{
    m_Name="New ROI";
    m_Scene=0;
    m_ROIRect = new ResizableItem(this,0);
    //m_ROIRect->setParentItem();

    m_ROIRect->setPos(500,500);
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

    if(newrect.width()>m_ROIRect->boundingRect().width() &&
            newrect.height()>m_ROIRect->boundingRect().height()){
        m_ROIRect->setVisible(true);
    }
    else{
        m_ROIRect->setVisible(false);
    }
}

void ROI::setScene(QGraphicsScene *Scene,QGraphicsPixmapItem* parentItem)
{


    if(m_Scene != Scene){
        if(m_Scene!=0)
            disconnect(m_Scene,SIGNAL(sceneRectChanged(QRectF)),this,0);
        m_Scene=Scene;
        if(m_Scene!=0)
            connect(m_Scene,SIGNAL(sceneRectChanged(QRectF)),this,SLOT(sceneRectChangedSlot(QRectF)));
       m_ROIRect->setParentItem(parentItem);

    }

}
ResizableItem *ROI::ROIRect() const
{
    return m_ROIRect;
}

void ROI::setROIRect(ResizableItem *ROIRect)
{
    m_ROIRect = ROIRect;
}



