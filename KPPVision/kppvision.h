#ifndef KPPVISION_H
#define KPPVISION_H

#include "kppvision_global.h"
#include <QtGui>
#include <QGraphicsView>
#include "request.h"
#include "kppvisionlist.h"
#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <string>
#include <fstream>
#include "kppcommon.h"
#include "kppvisionlist.h"

namespace Vision
{



class KPPVISIONSHARED_EXPORT KPPVision:public QObject
{

    Q_OBJECT

public:

    explicit KPPVision(QObject *parent = 0);

    ~KPPVision();
    QGraphicsView *getView() const;
    void setView(QGraphicsView *value);

    QString getName();
    void setName(const QString& name);


    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const KPPVision &vis);

    KPPVisionList<Request> *Requests() const;
    //void setRequests(KPPVisionList<Request> *Requests);






    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);
        ar & boost::serialization::make_nvp("Requests", m_Requests);
    }

private:
    QGraphicsView *view;
    QGraphicsScene *scene;

    QString m_Name;
    KPPVisionList<Request> *m_Requests;


signals:

public slots:

};


}


#endif // KPPVISION_H
