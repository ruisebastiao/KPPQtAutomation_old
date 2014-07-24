#include "kppvision.h"
#include "QDebug"
#include "kppvisionlist.cpp"

using namespace Vision;

KPPVision::KPPVision(QObject *parent, QString RootId) :
    icXmlSerializable(parent,RootId)
{

    m_Requests=new KPPVisionList<Request>(this,"Request List");

}


KPPVision::~KPPVision()
{
    //TODO Release Objects
    //delete rectitem;
}



QString KPPVision::getName()
{
    return m_Name;
}

void KPPVision::setName(const QString& name)
{
    m_Name = name;
}
KPPVisionList<Request> *KPPVision::Requests() const
{
    return m_Requests;
}





QGraphicsView *KPPVision::getView() const
{
    return view;
}

//static QImage IplImage2QImage(const IplImage *iplImage)
//{
//    int height = iplImage->height;
//    int width = iplImage->width;

//    if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 3)
//    {
//      const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
//      QImage img(qImageBuffer, width, height, QImage::Format_RGB888);
//      return img.rgbSwapped();
//    } else if  (iplImage->depth == IPL_DEPTH_8U && iplImage->nChannels == 1){
//    const uchar *qImageBuffer = (const uchar*)iplImage->imageData;
//    QImage img(qImageBuffer, width, height, QImage::Format_Indexed8);

//    QVector<QRgb> colorTable;
//    for (int i = 0; i < 256; i++){
//        colorTable.push_back(qRgb(i, i, i));
//    }
//    img.setColorTable(colorTable);
//    return img;
//    }else{
//      qWarning() << "Image cannot be converted.";
//      return QImage();
//    }
//}

void KPPVision::setView(QGraphicsView *value)
{
    //    view = value;

    //    scene= new QGraphicsScene(this);

    //    IplImage *image = cvLoadImage("c:\\Desert.jpg");
    //    //image = cvlo
    //    //QImage qImg = QImage((uchar *)image->imageData, image->width, image->height, QImage::Format_RGB888);
    //    IplImage* grayframe = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 1);

    //    cvCvtColor(image,grayframe,CV_BGR2GRAY);


    //    //grayframe->roi=rect2;


    //    QImage qImg = IplImage2QImage(grayframe);


    //    QGraphicsPixmapItem *item = scene->addPixmap(QPixmap::fromImage(qImg));

    //    ResizableItem* rectitem = new ResizableItem(0,item);
    //    rectitem->setPos(100,100);

    //   //scene->addItem(rectitem);

    //    view->setScene(scene);

    //    view->setSceneRect(0, 0, item->boundingRect().width(), item->boundingRect().height());
    //    view->fitInView(item,Qt::KeepAspectRatio);

    //    qreal x=rectitem->mapRectToParent(rectitem->boundingRect()).x();
    //    qreal y=rectitem->mapRectToParent(rectitem->boundingRect()).y();
    //    CvRect rect2=cvRect(x,y,rectitem->sceneBoundingRect().width(),rectitem->sceneBoundingRect().height());

    //    cvSetImageROI(grayframe, rect2);
    //    cvThreshold(grayframe,grayframe,120,0,cv::THRESH_BINARY);
    //    item->setPixmap(QPixmap::fromImage(IplImage2QImage(grayframe)));

}

bool    KPPVision::serialize(){

    //---------------
    //To serialize int, QString, float, bool, long, QDateTime
    //just call setSerialProperty
    //---------------


    setSerialProperty("Name", m_Name);
    if(m_Requests->rowCount(QModelIndex())>0)
        setSerialObject("Requests", m_Requests);


    return true;
}

bool    KPPVision::deserialize()
{

    //---------------
    //To deserialize int, QString, float, bool, long, QDateTime
    //just call getSerialProperty (returns a QVariant)
    //---------------

    m_Name = getSerialProperty("Name").toString();

    getSerialObject("Requests",m_Requests);
//    //return false;


    return true;
}
