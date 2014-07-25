#include "capturesource.h"
#include "kppcommon.h"

QString CaptureSource::SourceType()
{
    return ENUM_TO_STRING(CaptureSource,CaptureSourceTypes,m_SourceType);
}

