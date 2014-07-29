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
    inline void save( Archive& ar,const QStringSerializable& s, const unsigned int /*version*/ )
    {
        using boost::serialization::make_nvp;

        std::string varname;
        varname=s.getQStringName();
        QString* str=s.getQStringValue();
        ar << make_nvp(varname.c_str(), str->toStdString());
    }

    template<class Archive>
    inline void load( Archive& ar,const QStringSerializable& s, const unsigned int /*version*/ )
    {
        using boost::serialization::make_nvp;

         std::string varname;
         varname=s.getQStringName();
         std::string stdStr;
        ar >> make_nvp(varname.c_str(), stdStr);
        s.setStringValue(QString::fromStdString(stdStr));
    }
    template<class Archive>
    inline  void load(Archive & ar, const unsigned int version)
       {

    }

    template<class Archive>
    inline  void save(Archive & ar, const unsigned int version)
       {

    }

    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);

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
