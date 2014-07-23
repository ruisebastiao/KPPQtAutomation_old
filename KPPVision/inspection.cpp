#include "inspection.h"

using namespace Vision;


Inspection::Inspection(QObject *parent):
    icXmlSerializable(parent)
{

    m_Name="New Inspection";

}

Inspection::~Inspection()
{

}

QString Inspection::getName() const
{
    return m_Name;
}

void Inspection::setName(const QString &name)
{
    m_Name = name;
}



// icXmlSerializable interface

bool Inspection::serialize()
{
    setSerialProperty("Name", m_Name);

    return true;

}

bool Inspection::deserialize()
{
    m_Name = getSerialProperty("Name").toString();


    return  true;

}




/*

InspectionList::InspectionList(QObject *parent):
    icXmlSerializable(parent)
{
    m_Inspections=QList<Inspection*>();
}


QList<Inspection*> InspectionList::Inspections() const
{
    return m_Inspections;
}


Inspection *InspectionList::getInspection(const QString& name) const{

    for (int var = 0; var < m_Inspections.count(); ++var) {
        if(m_Inspections.at(var)->getTitle()==name)
            return m_Inspections.at(var);
    }

    return 0;
}


Inspection *InspectionList::getProjectAt(int pos) const{
    return m_Inspections.at(pos);
}



Inspection *InspectionList::AddInspection(const QString& name,QObject* parent){

    Inspection *insp = 0;

    for (int var = 0; var < m_Inspections.count(); ++var) {
        if (m_Inspections.at(var)->getTitle()==name) {
            return m_Inspections.at(var);
        }
    }

    insp = new Inspection(parent);
    insp->setTitle(name);

    AddInspection(insp,parent);


    return insp;
}

void InspectionList::AddInspection( Inspection *inspection,QObject* parent){
    int pos=0;
    if(m_Inspections.count()>=0) pos=m_Inspections.count();
    beginInsertRows(QModelIndex(), pos, pos);
    m_Inspections.append(inspection);
    endInsertRows();


}

QStringList *InspectionList::getInspectionNames(){
    QStringList *namesList=new QStringList();

    for (int var = 0; var < this->m_Inspections.count(); ++var) {
        namesList->append(m_Inspections.at(var)->getTitle());
    }

    return namesList;
}

Qt::ItemFlags InspectionList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool InspectionList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

                Inspection *inspection= m_Inspections.at(index.row());
                if(inspection==0) return false;
                inspection->setTitle(value.toString());

                emit dataChanged(index, index);
                return true;

         }
         return false;
}


int InspectionList::rowCount(const QModelIndex& parent) const {
        return m_Inspections.count();
    }

 QVariant  InspectionList::data(const QModelIndex& index, int role) const {
     // Check that the index is valid and within the correct range first:
     if (!index.isValid()) return QVariant();

     if (index.row() >= m_Inspections.count())
         return QVariant();

     if (role == Qt::DisplayRole) {
         //qDebug()<<;


         Inspection *inspection=getProjectAt(index.row());
         QString title=inspection->getTitle();
         return QVariant(title);

     }
     else if(role==Qt::UserRole){
         Inspection *insp=m_Inspections.at(index.row());
         return QVariant::fromValue<Inspection*>(insp);
     }
     else {
         return QVariant();
     }
 }




 void InspectionList::removeInspection(Inspection *insp){
     int position=m_Inspections.indexOf(insp);
     if(position>=0){
         beginRemoveRows(QModelIndex(), position, position);
         m_Inspections.removeOne(insp);
                 delete insp;
         endRemoveRows();
     }



 }


// icXmlSerializable interface

bool InspectionList::deserialize()
{
    int index, total;
    //step (a)
    total = getSerialObjectCount("Inspections");
    for (index=0; index < total; index++){

        //step (b)
        Inspection *inspection = new Inspection(this);

        //step (c)
        if (!getSerialObject("Inspections", inspection, index)){
            inspection->deleteLater();
            return false;
        }

        //step (d)
        m_Inspections.append(inspection);
    }
    return true;
}

bool InspectionList::serialize()
{
    setSerialObject("Inspections", m_Inspections);

    return true;
}
*/
