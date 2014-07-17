#ifndef CAMERAINFO_H
#define CAMERAINFO_H

#include "kpphardware_global.h"
#include "icxmlserializable.h"

namespace IDS {



class KPPHARDWARESHARED_EXPORT CameraInfo:public icXmlSerializable
{
    Q_OBJECT

public:
   // virtual operator QString() { return name; }
    //virtual void InitCamera();
    explicit CameraInfo(QObject *parent = 0, QString RootId="Camera");
private:
    QString name;



    // icXmlSerializable interface
protected:
    bool deserialize();
    bool serialize();
};
}
#endif // CAMERAINFO_H
