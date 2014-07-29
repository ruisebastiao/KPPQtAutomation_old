#ifndef BOOSTDEF_H
#define BOOSTDEF_H



namespace boost { namespace serialization {


template<class Archive>
inline void save( Archive& ar,const QStringSerializable &s, const unsigned int /*version*/ )
{
    using boost::serialization::make_nvp;

    std::string varname;
    varname=s.getQStringName();
    QString* str=s.getQStringValue();
    ar << make_nvp(varname.c_str(), str->toStdString());
}

template<class Archive>
inline void load( Archive& ar,const QStringSerializable& s, const unsigned int /*version*/ )
{
    using boost::serialization::make_nvp;

    std::string varname;
    varname=s.getQStringName();
    std::string stdStr;
    ar >> make_nvp(varname.c_str(), stdStr);
    s.setStringValue(QString::fromStdString(stdStr));
}


////---------------------------------------------------------------------------
///// Saves a QList object to a collection
//template<class Archive, class U >
//inline void save(Archive &ar, const QList< U > &t, const uint /* file_version */ )
//{
//    boost::serialization::stl::save_collection< Archive, QList<U> >(ar, t);
//}

////---------------------------------------------------------------------------
///// Loads a QList object from a collection
//template<class Archive, class U>
//inline void load(Archive &ar, QList<U > &t, const uint /* file_version */ )
//{
//    boost::serialization::stl::load_collection<
//            Archive,
//            QList<U>,
//            boost::serialization::stl::archive_input_seq<Archive, QList<U> >,
//            boost::serialization::stl::no_reserve_imp< QList<U> > >(ar, t);
//}
}

                }

#endif // BOOSTDEF_H
