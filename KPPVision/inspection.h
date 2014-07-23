#ifndef INSPECTION_H
#define INSPECTION_H

#include "kppvision_global.h"
#include <QObject>
#include <icxmlserializable.h>


namespace Vision
{

class KPPVISIONSHARED_EXPORT Inspection : public icXmlSerializable
{
    Q_OBJECT
public:
    explicit Inspection(QObject *parent = 0);
    ~Inspection();



    QString getName() const;
    void setName(const QString &name);

private:
    virtual bool serialize();
    virtual bool deserialize();

    QString m_Name;

signals:

public slots:

};

/*

    class KPPVISIONSHARED_EXPORT InspectionList:public icXmlSerializable
    {
        Q_OBJECT
    public:
        explicit InspectionList(QObject *parent = 0);




        Inspection *getInspection(const QString &name) const;
        Inspection *getProjectAt(int pos) const;
    private:
        QList<Inspection*>   m_Inspections;
    protected:
        // icXmlSerializable interface
        bool deserialize();
        bool serialize();

        // QAbstractItemModel interface
    public:
        int rowCount(const QModelIndex &parent) const;
        QVariant data(const QModelIndex &index, int role) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role);
        Qt::ItemFlags flags(const QModelIndex &index) const;

        QList<Inspection *> Inspections() const;

        Inspection *AddInspection(const QString &name, QObject *parent=0);
        void AddInspection(Inspection *inspection, QObject *parent=0);
        QStringList *getInspectionNames();
        void removeInspection(Inspection *insp);
    };

    */
}
#endif // INSPECTION_H
