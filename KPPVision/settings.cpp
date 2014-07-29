
#include "settings.h"

using namespace Vision;

Settings* Settings::AppSettings;


Settings::Settings(QObject *parent) :
    QObject(parent)
{
    m_ProjectsFilePath="teste";
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
KPPVisionList<KPPVision> *Settings::Projects() const
{

    return m_Projects;
}




bool Settings::Load(){

    return Load(m_location);
}

bool Settings::Save(){

    return Save(m_location);
}


bool Settings::Load(QString location){

    Settings *settings=this;
    try{
        m_location=location;


        std::ifstream ifs(location.toUtf8().data());
        if(!ifs.good()){

            return false;
        }
        boost::archive::xml_iarchive ia(ifs);

        // restore the schedule from the archive
        ia >> BOOST_SERIALIZATION_NVP(settings);

    }catch(...){
        return false;

    }

    return true;

}



    template<class Archive>
    inline void load( Archive& ar,const QStringSerializable& s, const unsigned int /*version*/ )
    {
        using boost::serialization::make_nvp;

        std::string varname;
        varname=s.getQStringName();
        std::string stdStr;
        ar >> make_nvp(varname.c_str(), stdStr);
        s.setStringValue(QString::fromStdString(stdStr));
    }



    template<class Archive>
    inline void save( Archive& ar,QStringSerializable s, const unsigned int /*version*/ )
    {
        using boost::serialization::make_nvp;

        std::string varname;
        varname=s.getQStringName();
        QString* str=s.getQStringValue();
        ar << make_nvp(varname.c_str(), str->toStdString());
    }


    template<class Archive>
    void Settings::serialize(Archive & ar, const unsigned int  file_version ){

        KPPVision teste();

        BOOST_SERIALIZATION_NVP(teste);
        boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_ProjectsFilePath),&m_ProjectsFilePath), file_version);


    }



    BOOST_SERIALIZATION_COLLECTION_TRAITS(QList)

bool Settings::Save(QString location){
    // make an archive
    Settings *settings=this;
        std::ofstream ofs(location.toUtf8().data());
        if(!ofs.good()){

            return false;
        }
        boost::archive::xml_oarchive oa(ofs);
        oa << BOOST_SERIALIZATION_NVP(settings);

    return true;
}
