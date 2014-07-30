#ifndef INSPECTION_H
#define INSPECTION_H

#include "kppvision_global.h"
#include <QObject>
#include "ilistviewitem.h"
#include "capturesource.h"
#include "BoostDef.h"

namespace Vision
{

class KPPVISIONSHARED_EXPORT Inspection :public QObject
{
    Q_OBJECT
public:
    explicit Inspection(QObject *parent = 0);
    ~Inspection();

    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const Inspection &insp);

    QString getName();
    void setName(const QString &name);

    CaptureSource *Capture() const;
    void setCapture(CaptureSource *capture);

private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);
        //ar & boost::serialization::make_nvp("Inspections", m_Inspections);
    }
    CaptureSource *m_capture;
    QString m_Name;

signals:

public slots:



};

}
#endif // INSPECTION_H
