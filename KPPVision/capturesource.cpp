#include "capturesource.h"
#include "kppcommon.h"

using namespace cv;

QString CaptureSource::getSourceTypeName()
{
 //   return ENUM_TO_STRING(CaptureSource,CaptureSourceTypes,m_SourceType);
    int index = metaObject()->indexOfEnumerator("CaptureSourceTypes");
    QMetaEnum metaEnum = metaObject()->enumerator(index);
    return metaEnum.valueToKey(m_SourceType);
}

QString CaptureSource::getSourceTypeName(CaptureSource::CaptureSourceTypes sourcetype)
{
    int index = staticMetaObject.indexOfEnumerator("CaptureSourceTypes");
    QMetaEnum metaEnum =staticMetaObject.enumerator(index);
    return metaEnum.valueToKey(sourcetype);
}
QTreeWidget *CaptureSource::TreeSettings() const
{
    return m_TreeSettings;
}

Mat CaptureSource::GetImage()
{
    return Mat();
}


CaptureSource::CaptureSourceTypes CaptureSource::getSourceTypeFromString(QString typeString)
{
    //   return ENUM_TO_STRING(CaptureSource,CaptureSourceTypes,m_SourceType);
    int index = staticMetaObject.indexOfEnumerator("CaptureSourceTypes");
    QMetaEnum metaEnum = staticMetaObject.enumerator(index);

    return (CaptureSource::CaptureSourceTypes)metaEnum.keyToValue(typeString.toStdString().c_str());
}

CaptureSource::CaptureSource(QObject *parent)
{

    m_TreeSettings= new QTreeWidget();
    m_TreeSettings->header()->setVisible(false);
    m_TreeSettings->setAutoFillBackground(true);

    //m_TreeSettings->setMinimumHeight(150);



    m_SourceType=None;
}

CaptureSource::CaptureSourceTypes CaptureSource::getSourceType()
{
    return m_SourceType;
}

QStringList CaptureSource::getSourceTypes()
{


    QStringList sourcetypes;

    int index = staticMetaObject.indexOfEnumerator("CaptureSourceTypes");
    QMetaEnum metaEnum = staticMetaObject.enumerator(index);
    for (int i = 0; i < metaEnum.keyCount(); i++)
    {
        sourcetypes.append(metaEnum.key(i)); // enum name as string

    }

    return sourcetypes;
}


