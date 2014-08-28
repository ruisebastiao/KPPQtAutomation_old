#include "inspection.h"
#include "capturesource.h"

#include "qdebug.h"

using namespace Vision;
using namespace cv;

Inspection::Inspection(QObject *parent):
    QObject(parent)
{

    m_Name="New Inspection";
    m_capture=new CaptureSource();
    m_InspectionScene= new KPPGraphicsScene(this);
    m_InspectionScene->setSceneRect(0,0,0,0);


    m_SelectionRect=0;


    m_ROIs=new KPPVisionList<ROI>(this);
    m_SelectedROI=0;

    m_view=0;

    m_BackgroundItem=m_InspectionScene->addPixmap(QPixmap());
    //m_ImageHolder=new ImageHolder();
    //m_InspectionScene->addItem(m_ImageHolder);

}

Inspection::~Inspection()
{
    m_CaptureImage.release();
    m_ProcessingImage.release();


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
                //roi->setScene(m_InspectionScene,m_ImageHolder);
                roi->setScene(m_InspectionScene,m_BackgroundItem);


            }
        }
    }
}

QGraphicsView *Inspection::getView() const
{
    return m_view;
}

void Inspection::UpdateScene(){

    if(m_view==0) return;

    if(m_CaptureImage.empty()){

        m_view->setScene(0);
        return;
    }



    if(m_view->scene()!=m_InspectionScene){
        m_view->setScene(m_InspectionScene);

        //m_InspectionScene->backgroundBrush()
    }



//    if(m_InspectionScene->sceneRect()!=m_BackgroundItem->boundingRect()){

//        m_InspectionScene->setSceneRect(m_BackgroundItem->boundingRect());



//    }


    m_view->fitInView(m_BackgroundItem,Qt::KeepAspectRatio);



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


ROI *Inspection::SelectedROI() const
{
    return m_SelectedROI;
}

void Inspection::setSelectedROI(ROI *SelectedROI)
{
    m_SelectedROI = SelectedROI;
}






bool Inspection::CaptureImage(){

    m_CaptureImage.release();
    m_ProcessingImage.release();
    m_CaptureImage= Capture()->GetImage(); //cvLoadImage("e:\\Desert.jpg");
    if(m_CaptureImage.empty()){
        return false;
    }


    return true;
}


void Inspection::Process(bool capture,bool process)
{


    if(capture){
        if(!CaptureImage())
            return;
    }

    cvtColor(m_CaptureImage,m_ProcessingImage,CV_BGR2RGB);



  //  m_ImageHolder->setImage(m_ProcessingImage);
   // m_ImageHolder->update(m_ImageHolder->boundingRect());




    if(process){
        for (int var = 0; var < ROIs()->rowCount(QModelIndex()); ++var) {
            ROI* roi=ROIs()->data(ROIs()->index(var,0),Qt::UserRole).value<ROI*>();
            if(roi!=0)
                roi->Process(m_ProcessingImage);
        }
    }

    m_BackgroundItem->setPixmap(QPixmap::fromImage(Vision::cvMat2QImage(m_ProcessingImage)));
    UpdateScene();


}


