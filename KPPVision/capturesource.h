#ifndef CAPTURESOURCE_H
#define CAPTURESOURCE_H

#include "kppvision_global.h"
#include "icxmlserializable.h"

#include <QObject>

class KPPVISIONSHARED_EXPORT CaptureSource:public icXmlSerializable
{
    Q_ENUMS(CaptureSourceTypes)
    Q_OBJECT
public:
    enum CaptureSourceTypes {
            ImageFile=0,
            IDSCamera=1
    };

    virtual CaptureSource* clone() const = 0;
    QString SourceType();
private:

protected:
      CaptureSourceTypes m_SourceType;
signals:

public slots:


      // icXmlSerializable interface
protected:
      virtual bool deserialize()=0;
      virtual bool serialize()=0;
};

#endif // CAPTURESOURCE_H
