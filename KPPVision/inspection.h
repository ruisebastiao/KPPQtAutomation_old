#ifndef INSPECTION_H
#define INSPECTION_H

#include "kppvision_global.h"
#include <QObject>
#include "kppvisionlist.h"
#include "qdebug.h"
#include "capturesource.h"
#include "qgraphicsview.h"
#include "QGraphicsPixmapItem"
#include "opencv2/opencv.hpp"
#include "kppgraphicsscene.h"
#include "kpproi.h"

#include "BoostDef.h"
#include "imageholder.h"

namespace Vision
{

class Request;

class KPPVISIONSHARED_EXPORT Inspection :public QObject
{
    Q_OBJECT
public:
    explicit Inspection(QObject *parent = 0);
    ~Inspection();

    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const Inspection &insp);

    QString getName();
    void setName(const QString &name);

    CaptureSource *Capture() const;
    void setCapture(CaptureSource *capture);
    void Process();
    void setView(QGraphicsView *view);
    QGraphicsView *getView() const;
    void UpdateScene();
    KPPVisionList<ROI> *ROIs() const;
    void setROIs(KPPVisionList<ROI> *ROIs);

    KPPGraphicsScene *InspectionScene() const;


    ROI *SelectedROI() const;
    void setSelectedROI(ROI *SelectedROI);

    IplImage *CaptureImage() const;


    IplImage *ProcessingImage() const;


private:
    ROI* m_SelectedROI;
    ResizableItem *m_SelectionRect;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {
        try{

            boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);
            ar & boost::serialization::make_nvp("Capture", m_capture);
            ar & boost::serialization::make_nvp("ROIs", m_ROIs);
        }
        catch(std::exception const&  ex)
        {

            qDebug()<<ex.what();
        }
    }


    QGraphicsView* m_view;
    KPPGraphicsScene* m_InspectionScene;

  //  QGraphicsPixmapItem *m_BackgroundItem;

    ImageHolder *m_ImageHolder;

    CaptureSource *m_capture;
    QString m_Name;
    KPPVisionList<ROI> *m_ROIs;
    IplImage *m_CaptureImage;
    IplImage *m_ProcessingImage;


signals:
    void CaptureSourceChanging();
    void CaptureSourceChanged();

public slots:



private slots:
    void SceneSelectionChanged();
};

}
#endif // INSPECTION_H
