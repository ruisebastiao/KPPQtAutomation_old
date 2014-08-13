#include "kppvision.h"
#include "QDebug"


using namespace Vision;

KPPVision::KPPVision(QObject *parent) :
    QObject(parent)
{

    m_Requests=new KPPVisionList<Request>(this);
    m_SelectedRequest=0;
}


KPPVision::~KPPVision()
{
    //TODO Release Objects
    //delete rectitem;
}



template<class Archive>
inline void save( Archive& ar,const QStringSerializable &s, const unsigned int /*version*/ )
{
    using boost::serialization::make_nvp;

    std::string varname;
    varname=s.getQStringName();
    QString* str=s.getQStringValue();
    ar << make_nvp(varname.c_str(), str->toStdString());
}

template<class Archive>
inline void load( Archive& ar,const QStringSerializable& s, const unsigned int /*version*/ )
{
    using boost::serialization::make_nvp;

    std::string varname;
    varname=s.getQStringName();
    std::string stdStr;
    ar >> make_nvp(varname.c_str(), stdStr);
    s.setStringValue(QString::fromStdString(stdStr));
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
Vision::Request *KPPVision::SelectedRequest() const
{
    return m_SelectedRequest;
}

void KPPVision::setSelectedRequest(Vision::Request *SelectedRequest)
{
    m_SelectedRequest = SelectedRequest;
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


template<class Archive>
inline  void load(Archive & ar, const unsigned int version)
{

}

template<class Archive>
inline  void save(Archive & ar, const unsigned int version)
{

}

