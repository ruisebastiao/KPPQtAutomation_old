#include "idscamerainfo.h"

using namespace IDS;

IDSCameraInfo::IDSCameraInfo(QObject *parent):
    CameraInfo(parent)
{
    m_ListCameras=0;
    UpdateCamerasList();

}

void IDSCameraInfo::InitCamera(int CameraId)
{

}

QHash<int, IDSCamera *> IDSCameraInfo::Cameras() const
{
    return m_Cameras;
}


void IDSCameraInfo::UpdateCamerasList()
{

    beginResetModel();
    INT nNumCam;
    if( is_GetNumberOfCameras( &nNumCam ) == IS_SUCCESS) {

        //qDebug()<<"Devices:"<<nNumCam;

        if( nNumCam >= 1 ) {
            // Create new list with suitable size

            m_ListCameras = (UEYE_CAMERA_LIST*) new BYTE [sizeof (DWORD) + nNumCam * sizeof (UEYE_CAMERA_INFO)];
            m_ListCameras->dwCount = nNumCam;

            //Retrieve camera info
            if (is_GetCameraList(m_ListCameras) == IS_SUCCESS) {



                int iCamera;
                for (iCamera = 0; iCamera < (int)m_ListCameras->dwCount; iCamera++) {

                    IDSCamera *newCam=new IDSCamera(this,(int)m_ListCameras->uci[iCamera].dwCameraID);

                    if (!m_Cameras.contains((int)m_ListCameras->uci[iCamera].dwCameraID)) {
                        m_Cameras.insert((int)m_ListCameras->uci[iCamera].dwCameraID,newCam);
                    }
                    else
                        delete newCam;
                }


            }

        }
    }

    endResetModel();
}



int IDSCameraInfo::rowCount(const QModelIndex &parent) const
{
    if (m_ListCameras==0) return 0;
    try{
        int ct=m_ListCameras->dwCount;
        return ct;
    }
    catch(...){
            return 0;
        }
}

QVariant IDSCameraInfo::data(const QModelIndex &index, int role) const
{


    // Check that the index is valid and within the correct range first:
    if (!index.isValid())
        return QVariant();

    if (index.row() >= (INT)m_ListCameras->dwCount)
        return QVariant();

    if (role == Qt::DisplayRole) {
        int camid= m_ListCameras->uci[index.row()].dwCameraID;
        QString cammodel= m_ListCameras->uci[index.row()].Model;
        //QString ret=tr("Name");
        QString ret=QString(cammodel).append(QString(" - ID:%1").arg(camid));
        //qDebug()<<"Ret:"<<ret;
        return QVariant(ret);
    } else if(role == Qt::UserRole){
        IDSCamera *cam=m_Cameras[(int)m_ListCameras->uci[index.row()].dwCameraID];
        return QVariant::fromValue<IDSCamera*>(cam);
    }
    else
        return QVariant();

}
