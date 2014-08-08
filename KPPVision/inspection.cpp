#include "inspection.h"
#include "capturesource.h"

#include "qdebug.h"
using namespace Vision;


Inspection::Inspection(QObject *parent):
    QObject(parent)
{

    m_Name="New Inspection";
    m_capture=new CaptureSource();
    m_InspectionScene= new KPPGraphicsScene(this);

    connect(m_InspectionScene,SIGNAL(selectionChanged()),this,SLOT(SceneSelectionChanged()));

    m_BackgroundItem = m_InspectionScene->addPixmap(QPixmap(0,0));

    m_SelectionRect=0;
    m_ROIs=new KPPVisionList<ROI>(this);
}

void Inspection::SceneSelectionChanged(){

//    if(m_InspectionScene->selectedItems().count()>1){
//        QGraphicsItem* item= m_InspectionScene->selectedItems().at(0);

//               if(item->parentItem()!=0){

//                   m_SelectionRect=new ResizableItem(this,m_capturePixmap);
//                   m_SelectionRect->Resize(new QRectF(item->parentItem()->childrenBoundingRect()));
//                   m_SelectionRect->setVisible(true);
//               }
//    }
//    else{
//        if(m_SelectionRect!=0){
//            m_SelectionRect->setParentItem(0);
//            delete m_SelectionRect;
//        }
//    }

//    if(m_selectiongroup!=0){
//        m_InspectionScene->destroyItemGroup(m_selectiongroup);
//        m_selectiongroup=0;
//    }

//    if(m_InspectionScene->selectedItems().count()>1){
//        //m_capturePixmap->setZValue(0);

//       m_selectiongroup=m_InspectionScene->createItemGroup(m_InspectionScene->selectedItems());
//       m_selectiongroup->setParentItem(m_capturePixmap);
//         m_selectiongroup->setZValue(10000);
//    }

}

Inspection::~Inspection()
{
    delete m_InspectionScene;
}

QString Inspection::getName()
{
    return m_Name;
}

void Inspection::setName(const QString &name)
{
    m_Name = name;
}



CaptureSource *Inspection::Capture() const
{
    return m_capture;
}

void Inspection::setCapture(CaptureSource *capture)
{
    if(capture!=m_capture){
        emit CaptureSourceChanging();
        delete m_capture;
        m_capture= capture;
        emit CaptureSourceChanged();
    }
}


void Inspection::setView(QGraphicsView* view)
{
    if(m_view!=view){
        m_view=view;
        for (int var = 0; var < m_ROIs->rowCount(QModelIndex()); ++var) {
            ROI* roi=m_ROIs->data(m_ROIs->index(var,0),Qt::UserRole).value<ROI*>();
            if(roi!=0){
                roi->setScene(m_InspectionScene,m_BackgroundItem);

                //m_InspectionScene->dra
            }
        }
    }
}

QGraphicsView *Inspection::getView() const
{
    return m_view;
}


static QImage IplImage2QImage(const IplImage *iplImage)
{
    int height = iplImage->height;
    int width = iplImage->width;

    if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
    {
        const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
        QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
        return img.rgbSwapped();
    } else if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1){
        const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
        QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);

        QVector<QRgb> colorTable;
        for (int i = 0; i < 256; i++){
            colorTable.push_back(qRgb(i, i, i));
        }
        img.setColorTable(colorTable);
        return img;
    }else{
        qWarning() << "Image cannot be converted.";
        return QImage();
    }
}
void Inspection::UpdateScene(){


  //  if(!m_capturePixmap->boundingRect().isEmpty()){
    if(m_view->scene()!=m_InspectionScene){
        m_view->setScene(m_InspectionScene);

        //m_InspectionScene->backgroundBrush()
    }

    if(m_InspectionScene->sceneRect()!=m_BackgroundItem->boundingRect()){
        //QRectF r=m_capturePixmap->boundingRect();
        m_InspectionScene->setSceneRect(m_BackgroundItem->boundingRect());

        m_view->updateSceneRect(m_InspectionScene->sceneRect());
        //m_view->setSceneRect(0, 0, m_capturePixmap->boundingRect().width(), m_capturePixmap->boundingRect().height());
        m_view->fitInView(m_BackgroundItem,Qt::KeepAspectRatio);


    }
//    if(ROIs()->getList().count()>0)
//        ROIs()->getList().at(0)->ROIRect()->setPos(500,500);
//    //QGraphicsItemGroup* group=m_InspectionScene->createItemGroup();
    //group->mo
    //m_InspectionScene->update(m_capturePixmap->boundingRect());
        //m_InspectionScene->;
  //  }

}
KPPVisionList<ROI> *Inspection::ROIs() const
{
    return m_ROIs;
}

void Inspection::setROIs(KPPVisionList<ROI> *ROIs)
{
    m_ROIs = ROIs;
}
KPPGraphicsScene *Inspection::InspectionScene() const
{
    return m_InspectionScene;
}
QGraphicsPixmapItem *Inspection::BackgroundItem() const
{
    return m_BackgroundItem;
}





void Inspection::Process()
{


    IplImage *image = Capture()->GetImage(); //cvLoadImage("e:\\Desert.jpg");

    if(image==0){
        //TODO verificar erro na captura
        return;
    }


    //image = cvlo
    //QImage qImg = QImage((uchar *)image->imageData, image->width, image->height, QImage::Format_RGB888);
    IplImage* grayframe = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

    cvCvtColor(image,grayframe,CV_BGR2GRAY);


    //grayframe->roi=rect2;


    QImage qImg = IplImage2QImage(grayframe);



    m_BackgroundItem->setPixmap(QPixmap::fromImage(qImg));

//    if(m_view->scene()!=m_InspectionScene)
//        m_view->setScene(m_InspectionScene);
    UpdateScene();

    //        ResizableItem* rectitem = new ResizableItem(0,item);
    //        rectitem->setPos(100,100);

    //       //scene->addItem(rectitem);

    //m_view->setScene(m_InspectionScene);
   // UpdateScene();

    //        view->setSceneRect(0, 0, item->boundingRect().width(), item->boundingRect().height());
    //        view->fitInView(item,Qt::KeepAspectRatio);

    //        qreal x=rectitem->mapRectToParent(rectitem->boundingRect()).x();
    //        qreal y=rectitem->mapRectToParent(rectitem->boundingRect()).y();
    //        CvRect rect2=cvRect(x,y,rectitem->sceneBoundingRect().width(),rectitem->sceneBoundingRect().height());

    //        cvSetImageROI(grayframe, rect2);
    //        cvThreshold(grayframe,grayframe,120,0,cv::THRESH_BINARY);
    //        item->setPixmap(QPixmap::fromImage(IplImage2QImage(grayframe)));

    cvReleaseImage(&image);
    cvReleaseImage(&grayframe);
}


