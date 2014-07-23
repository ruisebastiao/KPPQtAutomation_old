#ifndef KPPVISION_H
#define KPPVISION_H

#include "kppvision_global.h"
#include <QtGui>
#include <QGraphicsView>
#include <icxmlserializable.h>
#include "request.h"
#include "kppvisionlist.h"



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

    QString getName() const;
    void setName(const QString& name);



    KPPVisionList<Request> *Requests() const;
    //void setRequests(KPPVisionList<Request> *Requests);

private:
    QGraphicsView *view;
    QGraphicsScene *scene;

    QString m_Name;
    KPPVisionList<Request> *m_Requests;
    virtual bool serialize();

    virtual bool deserialize();

signals:

public slots:
};


}


#endif // KPPVISION_H
