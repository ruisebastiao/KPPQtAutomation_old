#ifndef SETTINGS_H
#define SETTINGS_H

#include "kppvision_global.h"
#include <QObject>
#include "kppvision.h"
#include "kpphardware.h"
#include "kppvisionlist.h"

#include "kppcommon.h"
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
#include "BoostDef.h"

using namespace Vision;


class KPPVISIONSHARED_EXPORT Settings :public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);

    static Settings *AppSettings;

    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const Settings &sett);


    QString ProjectsFilePath() const;
    void setProjectsFilePath(const QString &ProjectsFilePath);

    KPPHardware *Hardware() const;


    KPPVisionList<KPPVision> *Projects();




    bool Load(QString location);
    bool Save(QString location);
    bool Load();
    bool Save();



    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version);
private:
    QString m_location;
    QString m_ProjectsFilePath;
    KPPHardware *m_hardware;
    KPPVisionList<KPPVision> *m_Projects;

signals:

public slots:

};





#endif // SETTINGS_H
