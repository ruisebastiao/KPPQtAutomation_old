#ifndef CAMERAINFO_H
#define CAMERAINFO_H

#include "kpphardware_global.h"
#include "QAbstractListModel"

namespace IDS {



class KPPHARDWARESHARED_EXPORT CameraInfo:public QAbstractListModel
{
    Q_OBJECT

public:
   // virtual operator QString() { return name; }
    //virtual void InitCamera();
    explicit CameraInfo(QObject *parent = 0);
private:
    QString name;


};
}
#endif // CAMERAINFO_H
