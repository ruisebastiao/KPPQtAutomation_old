#include "kppvision.h"
#include "QDebug"

using namespace Vision;







KPPVision::KPPVision(QObject *parent, QString RootId) :
    icXmlSerializable(parent,RootId)
{

    m_inspectionList=new InspectionList(this);

}


KPPVision::~KPPVision()
{
    //TODO Release Objects
    //delete rectitem;
}



QString KPPVision::getTitle() const
{
    return m_title;
}

void KPPVision::setTitle(const QString& title)
{
    m_title = title;
}
InspectionList *KPPVision::inspectionList() const
{
    return m_inspectionList;
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


    setSerialProperty("title", m_title);
    if(m_inspectionList->Inspections().count()>0)
        setSerialObject("inspections", m_inspectionList);


    return true;
}

bool    KPPVision::deserialize(){

    //---------------
    //To deserialize int, QString, float, bool, long, QDateTime
    //just call getSerialProperty (returns a QVariant)
    //---------------

    m_title = getSerialProperty("title").toString();

    getSerialObject("inspections",m_inspectionList);
    //return false;


    return true;
}


//ProjectsList* ProjectsList::Projects;

ProjectsList::ProjectsList(QObject *parent,QString RootId) :
    icXmlSerializable(parent,RootId)
{

    m_title = "Projects List";

    m_Projects=QList<KPPVision*>();

}




QString ProjectsList::getTitle() const{
    return m_title;
}

void    ProjectsList::setTitle(const QString& title){
    m_title = title;
}


QStringList ProjectsList::getProjectNameList(){
    QStringList sections;



    for (int var = 0; var < m_Projects.count(); ++var) {
        sections.append(((KPPVision*)m_Projects.at(var))->getTitle());
    }


    return sections;
}


QList<KPPVision*> ProjectsList::getProjects(){
    return m_Projects;
}


KPPVision *ProjectsList::selectedPoject() const
{
    return m_selectedPoject;
}

void ProjectsList::setSelectedPoject(KPPVision *selectedPoject)
{
    m_selectedPoject = selectedPoject;
}




KPPVision *ProjectsList::getProject(const QString& name) const{

    for (int var = 0; var < m_Projects.count(); ++var) {
        if (m_Projects.at(var)->getTitle()==name) {
            return m_Projects.at(var);
        }
    }

    return 0;
}



KPPVision *ProjectsList::addProject(const QString& name,QObject* parent){
    KPPVision *project = 0;

    for (int var = 0; var < m_Projects.count(); ++var) {
        if (m_Projects.at(var)->getTitle()==name) {
            return m_Projects.at(var);
        }
    }

    project = new KPPVision(parent);
    project->setTitle(name);

    addProject(project,parent);

    return project;
}

void ProjectsList::addProject( KPPVision *project,QObject* parent){
    int pos=0;
    if(m_Projects.count()>=0) pos=m_Projects.count();
    beginInsertRows(QModelIndex(), pos, pos);
    m_Projects.append(project);
    endInsertRows();


}


void ProjectsList::removeProject(KPPVision *project){
    int position=m_Projects.indexOf(project);
    if(position>=0){
        beginRemoveRows(QModelIndex(), position, position);
        m_Projects.removeOne(project);
                delete project;
        endRemoveRows();
    }



}


Qt::ItemFlags ProjectsList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool ProjectsList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

            KPPVision *vis= m_Projects.at(index.row());
            if(vis==0) return false;
            vis->setTitle(value.toString());
            emit dataChanged(index, index);
            return true;

    }
    return false;
}


int ProjectsList::rowCount(const QModelIndex& parent) const {
    return m_Projects.count();
}

QVariant  ProjectsList::data(const QModelIndex& index, int role) const {
    // Check that the index is valid and within the correct range first:
    if (!index.isValid()) return QVariant();

    //        if(role == Qt::sizeHintRole){
    //            QVariant teste=index.data()
    //            return QSize(100,200);
    //        }
    if (index.row() >= m_Projects.count())
        return QVariant();

    if (role == Qt::DisplayRole) {
        //qDebug()<<;


        KPPVision *project=m_Projects.at(index.row());
        QString title=project->getTitle();
        return QVariant(title);
    }
    else if(role==Qt::UserRole){

        KPPVision *project=m_Projects.at(index.row());
        return QVariant::fromValue<KPPVision*>(project);

    }
    else {
        return QVariant();
    }
}


KPPVision* ProjectsList::searchProjectByTitle(const QString &title){

    for (int var = 0; var < m_Projects.count(); ++var) {
        if(m_Projects.at(var)->getTitle()==title){
            return m_Projects.at(var);
        }
    }


    return 0;
}


//----------------------------------------------------
//STEP 3: implements serialize & deserialize methods
//----------------------------------------------------



bool    ProjectsList::serialize(){

    //---------------
    //To serialize int, QString, float, bool, long, QDateTime
    //just call setSerialProperty
    //---------------
    setSerialProperty("title", m_title);


    //---------------
    //To serialize QObjects with icXmlSerializeble inheritance just call setSerialObject
    //You can use any from:
    //      icXmlSerializeble *
    //      QList<icXmlSerializeble *)
    //      QHash<QString, icXmlSerializeble *)
    //      QVector<icXmlSerializeble *)




    setSerialObject("Projects", m_Projects);

    //---------------
    //Always return a boolean
    //beacause you may want to include this object in another inner serialization
    //---------------



    return true;
}

bool    ProjectsList::deserialize(){

    //---------------
    //To deserialize int, QString, float, bool, long, QDateTime
    //just call getSerialProperty (returns a QVariant)
    //---------------
    m_title = getSerialProperty("title").toString();


    //-------------------
    //To deserialize QHash, QList, QVector:
    //  a) Obtain child count
    //  b) Instantiate each child
    //  c) Deserialize each child
    //  d) add to QHash, QList or QVector
    //-------------------
    int index, total;
    //step (a)
    total = getSerialObjectCount("Projects");
    for (index=0; index < total; index++){

        //step (b)
        KPPVision *project = new KPPVision(this);

        //step (c)
        if (!getSerialObject("Projects", project, index)){
            project->deleteLater();
            return false;
        }

        //step (d)
        m_Projects.append(project);
    }


    //---------------
    //Always return a boolean
    //beacause you may want to include this object in another inner serialization
    //---------------
    return true;
}
