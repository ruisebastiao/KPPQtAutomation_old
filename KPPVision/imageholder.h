#ifndef IMAGEHOLDER_H
#define IMAGEHOLDER_H

#include "opencv2/opencv.hpp"
#include <qgraphicsitem.h>

class ImageHolder : public QGraphicsItem
{
public:
    explicit ImageHolder(QGraphicsItem *parent = 0,IplImage* image=0);

private:
    cv::Mat m_Image;
    QImage InImage;
signals:

public slots:


    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    cv::Mat Image() const;
    void setImage(cv::Mat Image);
};

#endif // IMAGEHOLDER_H
