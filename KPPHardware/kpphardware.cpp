#include "kpphardware.h"
#include "string.h"
#include "exception"
#include "QImage"

using namespace IDS;


KPPHardware::KPPHardware(QObject *parent):
    QObject(parent)
{



    //IDS Cameras
    m_idsCameraInfo= new IDSCameraInfo(this);

}

IDSCameraInfo *KPPHardware::idsCameraInfo() const
{



    return  m_idsCameraInfo;

}






