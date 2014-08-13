#include "request.h"


using namespace Vision;

Request::Request(QObject *parent) :
    QObject(parent)
{
   // this->setObjectName("Request");
    m_Inspections=new KPPVisionList<Inspection>(this);
    m_SelectedInspection=0;
}
Vision::Inspection *Request::SelectedInspection() const
{
    return m_SelectedInspection;
}

void Request::setSelectedInspection(Vision::Inspection *SelectedInspection)
{
    m_SelectedInspection = SelectedInspection;
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
