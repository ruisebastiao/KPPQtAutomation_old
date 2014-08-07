#ifndef CAPTURESOURCE_H
#define CAPTURESOURCE_H

#include "kppvision_global.h"
#include <QMetaEnum>
#include <QObject>

#include "opencv2/opencv.hpp"

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include "qtreewidget.h"
#include "qheaderview.h"

class KPPVISIONSHARED_EXPORT CaptureSource:public QObject
{
    Q_ENUMS(CaptureSourceTypes)
    Q_OBJECT
public:
    enum CaptureSourceTypes {
        None=0,
        ImageFile=1
        //IDSCamera=2
    };


    friend class boost::serialization::access;

    CaptureSource(QObject* parent=0);
    CaptureSourceTypes getSourceType();
    static QStringList getSourceTypes();
    QString getSourceTypeName();

    static CaptureSource::CaptureSourceTypes getSourceTypeFromString(QString typeString);
    static QString getSourceTypeName(CaptureSource::CaptureSourceTypes sourcetype);
    QTreeWidget *TreeSettings() const;


    virtual IplImage* GetImage();

private:



    template<typename Archive>
    void serialize(Archive & ar, const unsigned int file_version) {
          //ar.register_type(static_cast<ImageFileCapture *>(NULL));
        }

protected:
    QTreeWidget *m_TreeSettings;
    CaptureSourceTypes m_SourceType;

signals:

public slots:


};


#endif // CAPTURESOURCE_H
