#include "camerainfo.h"

using namespace IDS;

CameraInfo::CameraInfo(QObject *parent, QString RootId):
    icXmlSerializable(parent,RootId)
{

}

bool CameraInfo::deserialize()
{
    return true;
}

bool CameraInfo::serialize()
{
    return true;
}
