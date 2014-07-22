#ifndef KPPVISION_H
#define KPPVISION_H

#include "kppvision_global.h"

#include <QtGui>
#include <QGraphicsView>

#include <icxmlserializable.h>
#include "inspection.h"


namespace Vision
{


class KPPVISIONSHARED_EXPORT KPPVision:public icXmlSerializable
{
    Q_OBJECT

public:

    explicit KPPVision(QObject *parent = 0,QString RootId="");

    ~KPPVision();
    QGraphicsView *getView() const;
    void setView(QGraphicsView *value);

    QString getTitle() const;
    void setTitle(const QString& getTitle);
    InspectionList *inspectionList() const;


private:
    QGraphicsView *view;
    QGraphicsScene *scene;

    QString m_title;
    InspectionList *m_inspectionList;
    virtual bool serialize();

    virtual bool deserialize();

signals:

public slots:
};


class KPPVISIONSHARED_EXPORT ProjectsList : public icXmlSerializable
{
    Q_OBJECT
public:
    explicit ProjectsList(QObject *parent = 0, QString RootId="Projects");
    QString getTitle() const;
    void setTitle(const QString &title);

    QStringList getProjectNameList();
    KPPVision *getProject(const QString &name) const;
    KPPVision *addProject(const QString &name,QObject *parent=0);
    KPPVision *searchProjectByTitle(const QString &title);


    QList<KPPVision *> getProjects();
    void removeProject(KPPVision *project);
    void addProject(KPPVision *project, QObject *parent);
    //KPPVision *getProjectAt(int pos) const;
    KPPVision *selectedPoject() const;
    void setSelectedPoject(KPPVision *selectedPoject);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
private:
    QString m_title;

    KPPVision* m_selectedPoject;

    QList<KPPVision*>   m_Projects;



    virtual bool serialize();
    virtual bool deserialize();


    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex &index) const;
signals:

public slots:

};
}


#endif // KPPVISION_H
