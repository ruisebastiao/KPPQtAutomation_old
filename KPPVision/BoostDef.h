
#ifndef BOOSTDEF_H
#define BOOSTDEF_H

#include "kppcommon.h"

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/filesystem.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/variant.hpp>

namespace boost
{

namespace serialization
{


template<class Archive>
void save( Archive& ar,const QStringSerializable &s, const unsigned int /*version*/ )
{
    using boost::serialization::make_nvp;

    std::string varname;
    varname=s.getQStringName();
    QString* str=s.getQStringValue();
    ar << make_nvp(varname.c_str(), str->toStdString());
}

template<class Archive>
void load( Archive& ar,const QStringSerializable& s, const unsigned int /*version*/ )
{
    using boost::serialization::make_nvp;

    std::string varname;
    varname=s.getQStringName();
    std::string stdStr;
    ar >> make_nvp(varname.c_str(), stdStr);
    s.setStringValue(QString::fromStdString(stdStr));
}

}

}

#endif // BOOSTDEF_H
