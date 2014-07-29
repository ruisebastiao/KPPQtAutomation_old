#ifndef KPPSERIALIZABLE_H
#define KPPSERIALIZABLE_H

#include "kppcommon.h"
#include <QObject>

#include <boost/serialization/string.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <string>
#include <fstream>

class KPPCOMMONSHARED_EXPORT KPPSerializable
{

public:
    explicit KPPSerializable();






signals:

public slots:

};

#endif // KPPSERIALIZABLE_H
