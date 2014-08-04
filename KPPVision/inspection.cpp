#include "inspection.h"
#include "capturesource.h"
using namespace Vision;


Inspection::Inspection(QObject *parent):
    QObject(parent)
{

    m_Name="New Inspection";
    m_capture=new CaptureSource();

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



CaptureSource *Inspection::Capture() const
{
    return m_capture;
}

void Inspection::setCapture(CaptureSource *capture)
{
    if(capture!=m_capture){
        emit CaptureSourceChanging();
        delete m_capture;
        m_capture= capture;
        emit CaptureSourceChanged();
    }
}


