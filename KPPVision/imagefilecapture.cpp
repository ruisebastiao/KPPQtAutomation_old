#include "imagefilecapture.h"
#include "kppcommon.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include "QVBoxLayout"
#include "qlineedit.h"
#include "qfiledialog.h"


BOOST_CLASS_EXPORT(ImageFileCapture);


ImageFileCapture::ImageFileCapture(QObject *parent):
CaptureSource(parent)
{


    m_SourceType=CaptureSourceTypes::ImageFile;

    m_TreeSettings->setIndentation(0);

     /////Image Loc
    QTreeWidgetItem* root_item=new QTreeWidgetItem;

    QFrame* frame_imgloc=new QFrame();
    frame_imgloc->setAutoFillBackground(false);
    frame_imgloc->setFrameShape(QFrame::NoFrame);
    frame_imgloc->setMaximumHeight(50);

    QHBoxLayout* layout_imgloc= new QHBoxLayout();
    layout_imgloc->setMargin(1);

    bt_imgloc= new KPPRootTreePushButton("Image Location",root_item);
    //bt_imgloc->setMinimumHeight(40);
    bt_imgloc->setMaximumWidth(110);
    connect(bt_imgloc,SIGNAL(clicked()),this,SLOT(bt_image_loc_clicked()));

    edit_img_path=new KPPLineEdit(m_TreeSettings);


    layout_imgloc->addWidget(bt_imgloc);
    layout_imgloc->addWidget(edit_img_path);
    frame_imgloc->setLayout(layout_imgloc);

    //////////////


   m_TreeSettings->addTopLevelItem(root_item);

   m_TreeSettings->setItemWidget(root_item,0,frame_imgloc);
   m_TreeSettings->setMaximumHeight(50);


}

void ImageFileCapture::bt_image_loc_clicked(){
    QFileDialog *d=new QFileDialog(0,Qt::Dialog);
    // d->setLocale(QLocale(QLocale::Portuguese, QLocale::Portugal));
    //d->createWindowContainer()
    //LookIn, FileName, FileType, Accept, Reject
    d->setLabelText( QFileDialog::Reject, tr("Cancel"));
    d->setLabelText( QFileDialog::LookIn, tr("Look In"));
    d->setFileMode(QFileDialog::AnyFile);
    d->setDefaultSuffix("bmp");
    d->setNameFilter(tr("Image Files (*.png *.jpg *.bmp)"));
    if(d->exec()){
        QString path=d->selectedFiles().at(0);
       edit_img_path->setText(path);
       m_imagepath=path;

    }
}

template< class Archive >
inline void save(Archive & ar, const CaptureSource::CaptureSourceTypes & t, unsigned int version)
{
    std::string c = CaptureSource::getSourceTypeName(t).toStdString();
    ar & boost::serialization::make_nvp("CaptureType",c);
}

template< class Archive >
inline void load(Archive & ar,CaptureSource::CaptureSourceTypes & t, unsigned int version)
{
    std::string c;
    ar & boost::serialization::make_nvp("CaptureType",c);
    QString sourcetypename;
    sourcetypename.fromStdString(c);
    t = CaptureSource::getSourceTypeFromString(sourcetypename);
}

 template<typename Archive>
void ImageFileCapture::serialize(Archive &ar, const unsigned int file_version)
{

         ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(CaptureSource);
          boost::serialization::split_free(ar,QStringSerializable(BOOST_STRINGIZE(m_imagepath),&m_imagepath), file_version);
          //ar & boost::serialization::make_nvp("ImageFileCapture", *this);
       // boost::serialization::split_free(ar,m_SourceType, file_version);
        edit_img_path->setText(m_imagepath);
}

