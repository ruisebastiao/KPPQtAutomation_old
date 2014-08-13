#ifndef KPPVISIONLIST_H
#define KPPVISIONLIST_H

#include "kppvision_global.h"
#include "qabstractitemmodel.h"
#include <string>
#include <fstream>
#include "kppcommon.h"
#include "qdebug.h"



#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

//BOOST_SERIALIZATION_SPLIT_FREE(QStringSerializable)

namespace Vision {





template<class T>
class KPPVISIONSHARED_EXPORT KPPVisionList :public QAbstractListModel
{
    //Q_OBJECT
public:
    friend class boost::serialization::access;
    friend std::ostream & operator<<(std::ostream &os, const KPPVisionList &sett);

    KPPVisionList(QObject *parent=0) :
        QAbstractListModel(parent)
    {




    }

    QString getName() const
    {

        return m_Name;
    }


    void setName(const QString &Name)
    {
        m_Name = Name;
    }


    QStringList getItemsNameList() const
    {
        QStringList names;

        for (int var = 0; var < m_InnerList.count(); ++var) {
            names.append(m_InnerList.at(var)->getName());
        }

        return names;
    }


    QList<T*> getList(){
        return m_InnerList;
    }


    T * getItemByName(const QString& name) const{

        for (int var = 0; var < m_InnerList.count(); ++var) {
            if (m_InnerList.at(var)->getName()==name) {
                return m_InnerList.at(var);
            }
        }

        return 0;
    }



    QModelIndex getItemModelIndex(T* Item){
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


    T * AddItem(const QString& name,QObject* parent=0){
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

        m_InnerList.append(item);

        QModelIndex idx=index(pos,0);

        beginInsertRows(idx, pos, pos);

        endInsertRows();


        return item;
    }


    void removeItem(T *item)
    {
        int position=m_InnerList.indexOf(item);
        if(position>=0){
            beginRemoveRows(QModelIndex(), position, position);
            m_InnerList.removeOne(item);
            delete item;
            endRemoveRows();
        }




    }


    Qt::ItemFlags flags(const QModelIndex &index) const
    {
        if (!index.isValid())
            return Qt::ItemIsEnabled;

        return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
    }



    int rowCount(const QModelIndex &parent) const
    {
        return m_InnerList.count();
    }



    QVariant data(const QModelIndex &index, int role) const
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

    bool setData(const QModelIndex &index, const QVariant &value, int role)
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

    bool Save(){
        return Save(m_location);
    }




    bool Save(QString location){
        std::string name=typeid(T).name();
        name=name.substr(name.find_last_of(':')+1);

        m_location=location;
        // make an archive
        //  KPPVisionList *VisionList=this;
        std::ofstream ofs(location.toUtf8().data());
        if(!ofs.good()){

            return false;
        }
        boost::archive::xml_oarchive oa(ofs);
        oa << boost::serialization::make_nvp("Projects", *this);

        return true;
    }

    bool Load(){
        return Load(m_location);
    }

    bool Load(QString location)
    {
        m_location=location;
        // KPPVisionList *VisionList=this;
        try{
            m_location=location;


            std::ifstream ifs(location.toUtf8().data());
            if(!ifs.good()){

                return false;
            }
            boost::archive::xml_iarchive ia(ifs);

            std::string name=typeid(T).name();
            name=name.substr(name.find_last_of(':')+1);
            ia >> boost::serialization::make_nvp("Projects", *this);
            //emit Loaded(this);

        }catch(...){
            return false;

        }


        return true;
    }


    template<class Archive>
    void serialize(Archive & ar,const unsigned int file_version){

        boost::serialization::split_free(ar,m_InnerList, file_version);
    }





    //BOOST_SERIALIZATION_SPLIT_MEMBER()

private:
    QString m_Name;
    QList<T*> m_InnerList;
    QString m_location;

signals:
    //void Loaded(QObject*);
public slots:







    // QAbstractItemModel interface
public:


    // QAbstractItemModel interface
public:

};


class Instantiations
{
private:
    void Instantiate();
};

}


BOOST_SERIALIZATION_COLLECTION_TRAITS(QList)



namespace boost
{
    namespace serialization
    {



    //---------------------------------------------------------------------------
    /// Saves a QList object to a collection
    template<class Archive, class U >
    inline void save(Archive &ar, const QList< U* > &t, const uint /* file_version */ )
    {

        boost::serialization::stl::save_collection< Archive, QList<U*> >(ar, t);
    }

    //---------------------------------------------------------------------------
    /// Loads a QList object from a collection
    template<class Archive, class U>
    inline void load(Archive &ar, QList<U *> &t, const uint /* file_version */ )
    {

        boost::serialization::stl::load_collection<
                Archive,
                QList<U*>,
                boost::serialization::stl::archive_input_seq<Archive, QList<U*> >,
                boost::serialization::stl::no_reserve_imp< QList<U*> > >(ar, t);

    }
    }
}
//BOOST_SERIALIZATION_SPLIT_FREE(QStringSerializable)




#endif // KPPVISIONLIST_H
