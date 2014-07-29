#include "request.h"
#include "kppvisionlist.cpp"

using namespace Vision;

Request::Request(QObject *parent) :
    QObject(parent)
{
   // this->setObjectName("Request");
    m_Inspections=new KPPVisionList<Inspection>(this);
}
KPPVisionList<Inspection> *Request::Inspections() const
{
    return m_Inspections;
}



QString Request::getName()
{
    return m_Name;
}

void Request::setName(const QString &name)
{
    m_Name=name;
}
