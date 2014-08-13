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
//m_InspectionScene->sele
    //m_BackgroundItem = m_InspectionScene->addPixmap(QPixmap(0,0));

    m_SelectionRect=0;


    m_ROIs=new KPPVisionList<ROI>(this);
    m_SelectedROI=0;

    m_ProcessingImage=0;
    m_CaptureImage=0;

    m_ImageHolder=new ImageHolder();
    m_InspectionScene->addItem(m_ImageHolder);
//m_InspectionScene->ant
}

void Inspection::SceneSelectionChanged(){


       // if(m_InspectionScene->selectedItems().count()==0)
        //ROI* selectedRoi=m_ParentRequest.Sel

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
    if(m_CaptureImage!=0)
        cvReleaseImage(&m_CaptureImage);
    if(m_ProcessingImage!=0)
        cvReleaseImage(&m_ProcessingImage);

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
                roi->setScene(m_InspectionScene,m_ImageHolder);

                //m_InspectionScene->dra
            }
        }
    }
}

QGraphicsView *Inspection::getView() const
{
    return m_view;
}


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
void Inspection::UpdateScene(){


    if(m_capture==0){
        m_view->setScene(0);
        return;
    }

    if(m_CaptureImage==0){
        m_view->setScene(0);
        return;
    }


    if(m_view->scene()!=m_InspectionScene){
        m_view->setScene(m_InspectionScene);

        //m_InspectionScene->backgroundBrush()
    }


    if(m_InspectionScene->sceneRect()!=m_ImageHolder->boundingRect()){
        //QRectF r=m_capturePixmap->boundingRect();
        m_InspectionScene->setSceneRect(m_ImageHolder->boundingRect());

        m_view->updateSceneRect(m_InspectionScene->sceneRect());
        //m_view->setSceneRect(0, 0, m_capturePixmap->boundingRect().width(), m_capturePixmap->boundingRect().height());
        m_view->fitInView(m_ImageHolder,Qt::KeepAspectRatio);


    }


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
IplImage *Inspection::CaptureImage() const
{
    return m_CaptureImage;
}
IplImage *Inspection::ProcessingImage() const
{
    return m_ProcessingImage;
}










void Inspection::Process()
{


    if(m_CaptureImage!=0)
        cvReleaseImage(&m_CaptureImage);
    if(m_ProcessingImage!=0)
        cvReleaseImage(&m_ProcessingImage);

    m_CaptureImage= Capture()->GetImage(); //cvLoadImage("e:\\Desert.jpg");

    if(m_CaptureImage==0){
        //TODO verificar erro na captura
        return;
    }



    //image = cvlo
    //QImage qImg = QImage((uchar *)image->imageData, image->width, image->height, QImage::Format_RGB888);
    m_ProcessingImage= cvCreateImage(cvGetSize(m_CaptureImage), IPL_DEPTH_8U, 1);

    cvCvtColor(m_CaptureImage,m_ProcessingImage,CV_BGR2GRAY);


    //grayframe->roi=rect2;


   // QImage qImg = IplImage2QImage(m_ProcessingImage);
    m_ImageHolder->setImage(m_ProcessingImage);
    m_ImageHolder->update(m_ImageHolder->boundingRect());
    for (int var = 0; var < ROIs()->rowCount(QModelIndex()); ++var) {
        ROI* roi=ROIs()->data(ROIs()->index(var,0),Qt::UserRole).value<ROI*>();
        if(roi!=0)
            roi->Process(m_ProcessingImage);
    }
    cvSetImageROI(m_ProcessingImage,cvRect(0,0,m_ProcessingImage->width,m_ProcessingImage->height));

    UpdateScene();




}


