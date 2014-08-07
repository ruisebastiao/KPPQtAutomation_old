#include "inspection.h"
#include "capturesource.h"

#include "qdebug.h"
using namespace Vision;


Inspection::Inspection(QObject *parent):
    QObject(parent)
{

    m_Name="New Inspection";
    m_capture=new CaptureSource();
    m_InspectionScene= new QGraphicsScene(this);
    m_capturePixmap = m_InspectionScene->addPixmap(QPixmap(0,0));
    m_ROIs=new KPPVisionList<ROI>(this);
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
    m_view=view;
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


    //m_view->setSceneRect(0,0,0,0);
    //m_view->invalidateScene();
    //m_view->setCacheMode();
    m_view->setScene(m_InspectionScene);
//    m_view->setSceneRect(0, 0, m_InspectionScene->width(), m_InspectionScene->height());
//    QList<QRectF> rects;
//    QRectF rect= m_view->sceneRect();
//    rects.append(rect);
//    m_view->updateScene(rects);

//    m_view->setSceneRect(0, 0, m_capturePixmap->boundingRect().width(), m_capturePixmap->boundingRect().height());
//    view->fitInView(m_capturePixmap,Qt::KeepAspectRatio);
    //m_view->setSceneRect(m_InspectionScene->sceneRect());
    //m_view->updateSceneRect(m_InspectionScene->sceneRect());


}
KPPVisionList<ROI> *Inspection::ROIs() const
{
    return m_ROIs;
}

void Inspection::setROIs(KPPVisionList<ROI> *ROIs)
{
    m_ROIs = ROIs;
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



        m_capturePixmap->setPixmap(QPixmap::fromImage(qImg));
//        ResizableItem* rectitem = new ResizableItem(0,item);
//        rectitem->setPos(100,100);

//       //scene->addItem(rectitem);

         m_view->setScene(m_InspectionScene);

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


