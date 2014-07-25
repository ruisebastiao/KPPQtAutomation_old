#ifndef IMAGEFILECAPTURE_H
#define IMAGEFILECAPTURE_H

#include "kppvision_global.h"
#include "capturesource.h"

class KPPVISIONSHARED_EXPORT ImageFileCapture : public CaptureSource
{
    Q_OBJECT
public:
    explicit ImageFileCapture(QObject *parent=0);
    //virtual ImageFileCapture* clone() const { return new CaptureSource(*this); }
private:


    // icXmlSerializable interface
protected:
    bool deserialize();
    bool serialize();
};

#endif // IMAGEFILECAPTURE_H
