#ifndef REQUEST_H
#define REQUEST_H

#include "kppvision_global.h"
#include "kppvisionlist.h"
#include "inspection.h"

namespace Vision {



class KPPVISIONSHARED_EXPORT Request:public QObject
{
    Q_OBJECT
public:
    explicit Request(QObject *parent = 0);
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const Request &req);
private:
    QString m_Name;
    KPPVisionList<Inspection> *m_Inspections;

    Vision::Inspection* m_SelectedInspection;




    template<class Archive>
    void serialize(Archive &ar, const unsigned int file_version)
    {
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_Name),&m_Name), file_version);
        ar & boost::serialization::make_nvp("Inspections", m_Inspections);
    }

signals:

public slots:




    // IVisionListItem interface
public:
    QString getName();
    void setName(const QString &name);
    KPPVisionList<Inspection> *Inspections() const;


    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Vision::Inspection *SelectedInspection() const;
    void setSelectedInspection(Vision::Inspection *SelectedInspection);
};
}
#endif // REQUEST_H
