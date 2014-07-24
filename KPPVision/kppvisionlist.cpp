#include "kppvisionlist.h"

using namespace Vision;

template<class T>
KPPVisionList<T>::KPPVisionList(QObject *parent, QString RootId) :
    icXmlSerializable(parent,RootId)
{
//    QString objname("KPPVisionList::");
//    objname.append(T.objectName());
//    this->setObjectName(objname);

}
template<class T>
QString KPPVisionList<T>::getName() const
{
    return m_Name;
}

template<class T>
void KPPVisionList<T>::setName(const QString &Name)
{
    m_Name = Name;
}

template<class T>
QStringList KPPVisionList<T>::getItemsNameList() const
{
    QStringList names;

    for (int var = 0; var < m_InnerList.count(); ++var) {
        names.append(m_InnerList.at(var)->getName());
    }

    return names;
}

template<class T>
QList<T*> KPPVisionList<T>::getList(){
    return m_InnerList;
}

template<class T>
T *KPPVisionList<T>::getItemByName(const QString& name) const{

    for (int var = 0; var < m_InnerList.count(); ++var) {
        if (m_InnerList.at(var)->getName()==name) {
            return m_InnerList.at(var);
        }
    }

    return 0;
}

template<class T>
T *KPPVisionList<T>::AddItem(const QString& name,QObject* parent){
    T *item = 0;

    for (int var = 0; var < m_InnerList.count(); ++var) {
        if (m_InnerList.at(var)->getName()==name) {
            return m_InnerList.at(var);
        }
    }

    item = new T(parent);
    item->setName(name);

    int pos=0;
    if(m_InnerList.count()>=0) pos=m_InnerList.count();
    beginInsertRows(QModelIndex(), pos, pos);
    m_InnerList.append(item);
    endInsertRows();


    return item;
}

template<class T>
void KPPVisionList<T>::removeItem(T *item)
{
    int position=m_InnerList.indexOf(item);
    if(position>=0){
        beginRemoveRows(QModelIndex(), position, position);
        m_InnerList.removeOne(item);
                delete item;
        endRemoveRows();
    }



}

template<class T>
Qt::ItemFlags KPPVisionList<T>::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


template<class T>
int KPPVisionList<T>::rowCount(const QModelIndex &parent) const
{
    return m_InnerList.count();
}
template<class T>
QVariant KPPVisionList<T>::data(const QModelIndex &index, int role) const
{
    // Check that the index is valid and within the correct range first:
    if (!index.isValid()) return QVariant();


    //        }
    if (index.row() >= m_InnerList.count())
        return QVariant();

    if (role == Qt::DisplayRole) {

        T *item=m_InnerList.at(index.row());
        QString name=item->getName();
        return QVariant(name);
    }
    else if(role==Qt::UserRole){

        T *item=m_InnerList.at(index.row());
        return QVariant::fromValue<T*>(item);

    }
    else {
        return QVariant();
    }

}
template<class T>
bool KPPVisionList<T>::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {

            T *item= m_InnerList.at(index.row());
            if(item==0) return false;
            for (int var = 0; var < m_InnerList.count(); ++var) {
                if(m_InnerList[var]->getName()==value.toString())
                    return false;
            }
            item->setName(value.toString());
            emit dataChanged(index, index);
            return true;

    }
    return false;
}



// icXmlSerializable interface
template<class T>
bool KPPVisionList<T>::deserialize()
{
    //---------------
    //To deserialize int, QString, float, bool, long, QDateTime
    //just call getSerialProperty (returns a QVariant)
    //---------------
    m_Name = getSerialProperty("Name").toString();


    //-------------------
    //To deserialize QHash, QList, QVector:
    //  a) Obtain child count
    //  b) Instantiate each child
    //  c) Deserialize each child
    //  d) add to QHash, QList or QVector
    //-------------------
    int index, total;
    //step (a)
    total = getSerialObjectCount("List");
    for (index=0; index < total; index++){

        //step (b)
        T *item = new T(this);

        //step (c)
        if (!getSerialObject("List", item, index)){
            item->deleteLater();
            return false;
        }

        //step (d)
        m_InnerList.append(item);
    }


    //---------------
    //Always return a boolean
    //beacause you may want to include this object in another inner serialization
    //---------------
    return true;
}
template<class T>
bool KPPVisionList<T>::serialize()
{
    //---------------
    //To serialize int, QString, float, bool, long, QDateTime
    //just call setSerialProperty
    //---------------
    setSerialProperty("Name", m_Name);


    //---------------
    //To serialize QObjects with icXmlSerializeble inheritance just call setSerialObject
    //You can use any from:
    //      icXmlSerializeble *
    //      QList<icXmlSerializeble *)
    //      QHash<QString, icXmlSerializeble *)
    //      QVector<icXmlSerializeble *)




    setSerialObject("List", m_InnerList);

    //---------------
    //Always return a boolean
    //beacause you may want to include this object in another inner serialization
    //---------------



    return true;
}
