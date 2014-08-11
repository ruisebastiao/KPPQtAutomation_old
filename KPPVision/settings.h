#ifndef SETTINGS_H
#define SETTINGS_H

#include "kppvision_global.h"
#include <QObject>
#include "kppvision.h"
#include "kpphardware.h"
#include "kppvisionlist.h"

#include "kppcommon.h"

#include <string>
#include <fstream>
#include "BoostDef.h"
#include "qwidget.h"

using namespace Vision;


class KPPVISIONSHARED_EXPORT Settings :public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0);

    static Settings *AppSettings;
    static QWidget* mainwidget;
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
