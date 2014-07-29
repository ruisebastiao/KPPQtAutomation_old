#include "kppvisionlist.h"

using namespace Vision;

template<class T>
KPPVisionList<T>::KPPVisionList(QObject *parent) :
    QAbstractListModel(parent)
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
QModelIndex KPPVisionList<T>::getItemModelIndex(T* Item){
    QModelIndex modelIndex;
    QModelIndexList Items =match(
                index(0, 0),
                Qt::DisplayRole,
                QVariant::fromValue(Item->getName()),
                2, // look *
                Qt::MatchRecursive); // look *
    if(Items.count()>0){
        modelIndex=index(Items.at(0).row(),0);
    }

    return modelIndex;
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



