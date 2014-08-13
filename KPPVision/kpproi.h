#ifndef KPPROI_H
#define KPPROI_H

#include <QObject>
#include "opencv2/opencv.hpp"

#include "BoostDef.h"
#include "kppvision_global.h"
#include "resizableitem.h"
#include "QGraphicsScene"
#include "imageholder.h"

namespace Vision {



class KPPVISIONSHARED_EXPORT ROI : public ResizableItem
{
    Q_OBJECT
public:
    explicit ROI(QObject *parent = 0);
    //~ROI();
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const ROI &roi);


    QString getName() const;
    void setName(const QString &Name);

    QGraphicsScene *Scene() const;
    void setScene(QGraphicsScene *Scene, QGraphicsItem *parentItem);

//    ResizableItem *ROIRect() const;
//    void setROIRect(ResizableItem *ROIRect);
    void Process(IplImage *processingImage);



private:
    IplImage* m_ProcessingImage;

    QString m_Name;
    QGraphicsScene* m_Scene;

    qreal roi_x;
    qreal roi_y;
    qreal roi_w;
    qreal roi_h;

    //ResizableItem* m_ROIRect;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ResizableItem);
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);

        //ar & boost::serialization::make_nvp("m_ROIRect", m_ROIRect);

    }



signals:
    void ROIPressed(ROI* roi);

public slots:
 void sceneRectChangedSlot(QRectF newrect);
private slots:


 // QGraphicsItem interface
protected:
 void mousePressEvent(QGraphicsSceneMouseEvent *event);

 // QGraphicsItem interface
public:

};
}
#endif // KPPROI_H
