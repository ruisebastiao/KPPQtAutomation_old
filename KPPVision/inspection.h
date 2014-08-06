#ifndef INSPECTION_H
#define INSPECTION_H

#include "kppvision_global.h"
#include <QObject>
#include "ilistviewitem.h"
#include "capturesource.h"
#include "qgraphicsview.h"

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
    void Process();
    void setView(QGraphicsView *view);
    QGraphicsView *getView() const;
private:
    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);
        ar & boost::serialization::make_nvp("Capture", m_capture);
    }


    QGraphicsView* m_view;

    CaptureSource *m_capture;
    QString m_Name;

signals:
    void CaptureSourceChanging();
    void CaptureSourceChanged();

public slots:



};

}
#endif // INSPECTION_H
