#ifndef KPPROI_H
#define KPPROI_H

#include <QObject>
#include "opencv2/opencv.hpp"

#include "BoostDef.h"
#include "kppvision_global.h"
#include "resizableitem.h"
#include "QGraphicsScene"

namespace Vision {


class KPPVISIONSHARED_EXPORT ROI : public QObject
{
    Q_OBJECT
public:
    explicit ROI(QObject *parent = 0);

    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const ROI &roi);


    QString getName() const;
    void setName(const QString &Name);

    QGraphicsScene *Scene() const;
    void setScene(QGraphicsScene *Scene, QGraphicsPixmapItem *parentItem);

    ResizableItem *ROIRect() const;
    void setROIRect(ResizableItem *ROIRect);

private:
    QString m_Name;
    QGraphicsScene* m_Scene;
    ResizableItem* m_ROIRect;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {

        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);


    }



signals:

public slots:
 void sceneRectChangedSlot(QRectF newrect);
private slots:

};
}
#endif // KPPROI_H
