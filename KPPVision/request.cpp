#include "request.h"
#include "kppvisionlist.cpp"

using namespace Vision;

Request::Request(QObject *parent) :
    icXmlSerializable(parent)
{
   // this->setObjectName("Request");
    m_Inspections=new KPPVisionList<Inspection>(this,"Inspections List");
}
KPPVisionList<Inspection> *Request::Inspections() const
{
    return m_Inspections;
}



bool Request::deserialize()
{
    m_Name = getSerialProperty("Name").toString();
    getSerialObject("Inspections",m_Inspections);

    return  true;
}

bool Request::serialize()
{
    setSerialProperty("Name", m_Name);
    if(m_Inspections->rowCount(QModelIndex())>0)
        setSerialObject("Inspections", m_Inspections);

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
