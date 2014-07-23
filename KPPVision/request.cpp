#include "request.h"

Request::Request(QObject *parent) :
    icXmlSerializable(parent)
{
}


bool Request::deserialize()
{
    m_Name = getSerialProperty("Name").toString();


    return  true;
}

bool Request::serialize()
{
    setSerialProperty("Name", m_Name);

    return true;
}


QString Request::getName()
{
    return m_Name;
}

void Request::setName(const QString &name)
{
    m_Name=name;
}
