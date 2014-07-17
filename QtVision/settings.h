#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "kppvision.h"
#include "kpphardware.h"

#include "icxmlserializable.h"

using namespace Vision;


class Settings : public icXmlSerializable
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent = 0, QString RootId="Settings");
    static Settings *AppSettings;



    QString ProjectsFilePath() const;
    void setProjectsFilePath(const QString &ProjectsFilePath);

    KPPHardware *Hardware() const;
    //void setHardware(KPPHardware *hardware);

    ProjectsList *Projects() const;
    //void setProjects(ProjectsList *Projects);

private:
    QString m_ProjectsFilePath;
    KPPHardware *m_hardware;
    ProjectsList *m_Projects;
    virtual bool    serialize();
    virtual bool    deserialize();
signals:

public slots:

};



#endif // SETTINGS_H
