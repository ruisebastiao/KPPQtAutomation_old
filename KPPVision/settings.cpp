#include "settings.h"


Settings* Settings::AppSettings;

Settings::Settings(QObject *parent,QString RootId) :
    icXmlSerializable(parent,RootId)
{
  m_ProjectsFilePath="";
  AppSettings=this;
  m_hardware= new KPPHardware(this);
  m_Projects=new ProjectsList(this);
}
QString Settings::ProjectsFilePath() const
{
    return m_ProjectsFilePath;
}

void Settings::setProjectsFilePath(const QString &ProjectsFilePath)
{
    m_ProjectsFilePath = ProjectsFilePath;
}
KPPHardware *Settings::Hardware() const
{
    return m_hardware;
}
ProjectsList *Settings::Projects() const
{
    return m_Projects;
}


//void Settings::setHardware(KPPHardware *hardware)
//{
//    m_hardware = hardware;
//}




//bool Settings::rowCount(const QModelIndex &parent) const{
//    return true;
//}

//QVariant Settings::data(const QModelIndex &index, int role) const{
//    return QVariant();
//}



//----------------------------------------------------
//STEP 3: implements serialize & deserialize methods
//----------------------------------------------------

bool    Settings::serialize(){

    //---------------
    //To serialize int, QString, float, bool, long, QDateTime
    //just call setSerialProperty
    //---------------
    setSerialProperty("ProjectsFilePath", m_ProjectsFilePath);
    setSerialObject("Hardware",m_hardware);
   // setSerialProperty("price", m_price);
    //setSerialProperty("title", m_title);
    //setSerialProperty("author", m_author);
    //setSerialProperty("date", m_date);

    return true;
}

bool    Settings::deserialize(){

    //---------------
    //To deserialize int, QString, float, bool, long, QDateTime
    //just call getSerialProperty (returns a QVariant)
    //---------------
    m_ProjectsFilePath = getSerialProperty("ProjectsFilePath").toString();
    //m_hardware = new hardware(this);
    //getSerialObject("hardware",m_hardware);

//    m_price = getSerialProperty("price").toFloat();
//    m_title = getSerialProperty("title").toString();
//    m_author = getSerialProperty("author").toString();
//    m_date = getSerialProperty("date").toDateTime();

    return true;
}




