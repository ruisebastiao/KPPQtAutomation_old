#ifndef KPPHARDWARE_H
#define KPPHARDWARE_H

#include "kpphardware_global.h"
#include "QImage"
#include <QObject>
#include <icxmlserializable.h>
#include "idscamerainfo.h"




class KPPHARDWARESHARED_EXPORT KPPHardware : public icXmlSerializable
{
    Q_OBJECT
public:
    explicit KPPHardware(QObject *parent = 0, QString RootId="Hardware");

    // QList<CameraInfo> *getcamerasInfo() const;


    IDS::IDSCameraInfo *idsCameraInfo() const;
    //void setIdsCameraInfo(IDSCameraInfo *idsCameraInfo);

private:
    IDS::IDSCameraInfo* m_idsCameraInfo;
signals:

public slots:


    // icXmlSerializable interface
protected:
    bool deserialize();
    bool serialize();
};




#endif // KPPHARDWARE_H
