#include "imagefilecapture.h"
#include "kppcommon.h"

ImageFileCapture::ImageFileCapture(QObject *parent)
{
    m_SourceType=CaptureSourceTypes::ImageFile;

}


bool ImageFileCapture::deserialize()
{

    //this=clone();
    QString type_str=getSerialProperty("Type").toString();


    m_SourceType=STRING_TO_ENUM(CaptureSource,CaptureSourceTypes,type_str);

    return  true;

}

bool ImageFileCapture::serialize()
{

     setSerialProperty("Type", SourceType());

     return true;
}
