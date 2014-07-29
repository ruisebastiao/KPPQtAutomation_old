#ifndef INSPECTION_H
#define INSPECTION_H

#include "kppvision_global.h"
#include <QObject>
#include "ilistviewitem.h"
#include "capturesource.h"

namespace Vision
{

class KPPVISIONSHARED_EXPORT Inspection :public QObject
{
    Q_OBJECT
public:
    explicit Inspection(QObject *parent = 0);
    ~Inspection();



    QString getName();
    void setName(const QString &name);

    CaptureSource *Capture() const;
    void setCapture(CaptureSource *capture);

private:

    CaptureSource *m_capture;
    QString m_Name;

signals:

public slots:



};

}
#endif // INSPECTION_H
