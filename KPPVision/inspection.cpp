#include "inspection.h"

using namespace Vision;


Inspection::Inspection(QObject *parent):
    icXmlSerializable(parent)
{

    m_Name="New Inspection";
    m_capture=0;
}

Inspection::~Inspection()
{

}

QString Inspection::getName()
{
    return m_Name;
}

void Inspection::setName(const QString &name)
{
    m_Name = name;
}



// icXmlSerializable interface

bool Inspection::serialize()
{
    setSerialProperty("Name", m_Name);


    return true;

}

bool Inspection::deserialize()
{
    m_Name = getSerialProperty("Name").toString();
    //getSerialObject("CaptureSource");

    return  true;

}
CaptureSource *Inspection::Capture() const
{
    return m_capture;
}

void Inspection::setCapture(CaptureSource *capture)
{
    m_capture= capture;
}


