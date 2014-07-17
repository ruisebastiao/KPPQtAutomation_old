#include "kpphardware.h"
#include "string.h"
#include "exception"
#include "QImage"

using namespace IDS;


KPPHardware::KPPHardware(QObject *parent, QString RootId):
    icXmlSerializable(parent,RootId)
{



    //IDS Cameras
    m_idsCameraInfo= new IDSCameraInfo(this);

}

IDSCameraInfo *KPPHardware::idsCameraInfo() const
{



    return  m_idsCameraInfo;

}






bool KPPHardware::deserialize()
{

    return true;
}

bool KPPHardware::serialize()
{
    return true;
}

