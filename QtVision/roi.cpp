#include "roi.h"

using namespace Vision;



ROI::ROI(QObject *parent):
 icXmlSerializable(parent)
{

    m_title="New ROI";
}

ROI::~ROI()
{

}

QString ROI::title() const
{
    return m_title;
}

void ROI::setTitle(const QString &title)
{
    m_title = title;
}

ResizableItem *ROI::getROIrect() const
{
    return m_ROIrect;
}

void ROI::setROIrect(ResizableItem *value)
{
    m_ROIrect = value;
}


 // icXmlSerializable interface

bool ROI::serialize()
{
     setSerialProperty("title", m_title);

     setSerialObject("ROIrect", m_ROIrect);
     return true;

}

bool ROI::deserialize()
{
    m_title = getSerialProperty("title").toString();
    m_ROIrect=new ResizableItem();
    if(!getSerialObject("ROIrect",m_ROIrect))
        m_ROIrect->deleteLater();

    return  true;

}



ROIList::ROIList(QObject *parent):
    icXmlSerializable(parent,"ROIList")
{

}
QHash<QString, icXmlSerializable *> ROIList::ROIs() const
{
    return m_ROIs;
}


ROI *ROIList::getProject(const QString& name) const{
    ROI *roi = 0;
    if (m_ROIs.contains(name)) {
        roi = (ROI *)m_ROIs.value(name);
    }

    return roi;
}


ROI *ROIList::getProjectAt(int pos) const{

    int k=-1;
    ROI *roi=0;
    QHashIterator<QString, icXmlSerializable*> i(m_ROIs);

    while (i.hasNext()) {
        i.next();
        k++;
        if(k==pos){
            roi=(ROI *)i.value();
            break;
        }

    }

    return roi;
}

// QAbstractItemModel interface

Qt::ItemFlags ROIList::flags(const QModelIndex &index) const
{
    if (!index.isValid())
             return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool ROIList::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
            if(!m_ROIs.contains(value.toString())){
                ROI *roi= getProject(index.data().toString());
                m_ROIs.remove(roi->title());
                roi->setTitle(value.toString());
                m_ROIs.insert(roi->title(),roi);


                emit dataChanged(index, index);
                return true;
            }
         }
         return false;
}


int ROIList::rowCount(const QModelIndex& parent) const {
        return m_ROIs.count();
    }

 QVariant  ROIList::data(const QModelIndex& index, int role) const {
     // Check that the index is valid and within the correct range first:
     if (!index.isValid()) return QVariant();

//        if(role == Qt::sizeHintRole){
//            QVariant teste=index.data()
//            return QSize(100,200);
//        }
     if (index.row() >= m_ROIs.count())
         return QVariant();

     if (role == Qt::DisplayRole) {
         //qDebug()<<;


         ROI *roi=getProjectAt(index.row());
         QString title=roi->title();
         return QVariant(title);
     } else {
         return QVariant();
     }
 }
// icXmlSerializable interface

bool ROIList::deserialize()
{
    int index, total;
    //step (a)
    total = getSerialObjectCount("ROIs");
    for (index=0; index < total; index++){

        //step (b)
        ROI *roi = new ROI(this);

        //step (c)
        if (!getSerialObject("ROIs", roi, index)){
            roi->deleteLater();
            return false;
        }

        //step (d)
        m_ROIs.insert(roi->title(), roi);
    }
    return true;
}

bool ROIList::serialize()
{
    setSerialObject("ROIs", m_ROIs);

    return true;
}




