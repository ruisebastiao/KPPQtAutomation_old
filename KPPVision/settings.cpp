
#include "settings.h"





using namespace Vision;

Settings* Settings::AppSettings=0;
QWidget* Settings::mainwidget=0;

Settings::Settings(QObject *parent) :
    QObject(parent)
{
    m_ProjectsFilePath="No path";
    AppSettings=this;
    m_hardware= new KPPHardware(this);
    m_Projects=new KPPVisionList<KPPVision>(this);
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
KPPVisionList<KPPVision> *Settings::Projects()
{

    return m_Projects;
}




    template<class Archive>
    void Settings::serialize(Archive & ar, const unsigned int  file_version ){

               //ar &   BOOST_SERIALIZATION_NVP(m_Projects);
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_ProjectsFilePath),&m_ProjectsFilePath), file_version);




    }



bool Settings::Save(QString location){
    // make an archive
    //Settings *settings=this;
        std::ofstream ofs(location.toUtf8().data());
        if(!ofs.good()){

            return false;
        }
        boost::archive::xml_oarchive oa(ofs);
        //oa << BOOST_SERIALIZATION_NVP(settings);
         oa << boost::serialization::make_nvp("Settings", *this);

    return true;
}

bool Settings::Load(){

    return Load(m_location);
}

bool Settings::Save(){

    return Save(m_location);
}


bool Settings::Load(QString location){


    try{
        m_location=location;


        std::ifstream ifs(location.toUtf8().data());
        if(!ifs.good()){

            return false;
        }
        boost::archive::xml_iarchive ia(ifs);

        // restore the schedule from the archive
        //ia >> BOOST_SERIALIZATION_NVP(settings);
         ia >> boost::serialization::make_nvp("Settings", *this);
        //AppSettings=settings;

    }catch(...){
        return false;

    }

    return true;

}
