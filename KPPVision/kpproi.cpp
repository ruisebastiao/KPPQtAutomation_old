#include "kpproi.h"

using namespace Vision;

ROI::ROI(QObject *parent) :
    QObject(parent)
{
    m_Name="New ROI";
}
QString ROI::getName() const
{
    return m_Name;
}

void ROI::setName(const QString &Name)
{
    m_Name = Name;
}

