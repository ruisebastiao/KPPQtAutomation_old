#include "idscamera.h"
#include "qdebug.h"

using namespace IDS;


IDSCamera::IDSCamera(QObject *parent, int cameraID,QWidget *parentWidget):
    QObject(parent)
{
    m_nRenderMode = IS_RENDER_FIT_TO_WINDOW;
    m_framethread=0;
    Eventhandlers[0]=0;
    Eventhandlers[1]=0;
    m_State=Stopped;
    m_RunMode=Snap;
    m_CameraHandler=cameraID;
    m_ImageHeigth=0;
    m_ImageWidth=0;
    m_ImageAOIs=new CameraImageAOIModel(this);
    m_formatsAvaible=0;

}

IDSCamera::~IDSCamera()
{
    //stopThreadFrame();
    setState(Stopped);

    delete m_ImageAOIs;


}

void IDSCamera::CleanupSettings(){
    if(m_formatsAvaible!=0)
        free(m_formatsAvaible);
    m_ImageAOIs->RemoveAll();
}

void IDSCamera::InitializeSettings(){

    CleanupSettings();

    // Get number of available formats and size of list
    UINT count;
    UINT bytesNeeded = sizeof(IMAGE_FORMAT_LIST);
    INT nRet = is_ImageFormat(m_CameraHandler, IMGFRMT_CMD_GET_NUM_ENTRIES, &count, 4);
    bytesNeeded += (count - 1) * sizeof(IMAGE_FORMAT_INFO);
    void* ptr = malloc(bytesNeeded);

    // Create and fill list
    m_formatsAvaible = (IMAGE_FORMAT_LIST*) ptr;
    m_formatsAvaible->nSizeOfListEntry = sizeof(IMAGE_FORMAT_INFO);
    m_formatsAvaible->nNumListElements = count;
    nRet = is_ImageFormat(m_CameraHandler, IMGFRMT_CMD_GET_LIST, m_formatsAvaible, bytesNeeded);
    IMAGE_FORMAT_INFO formatInfo;
    for (int i = 0; i < count; i++)
    {
        formatInfo = m_formatsAvaible->FormatInfo[i];
        m_ImageAOIs->AddImageAOI(new CameraImageAOI(this,formatInfo));


    }



}

bool IDSCamera::stopThreadFrame(){



    if(m_framethread!=0) {
#ifdef _WIN32
        SetEvent(Eventhandlers[1]);
#endif
        m_framethread->quit();
        if(!m_framethread->wait(5000)) //Wait until it actually has terminated (max. 5 sec)
        {
            qWarning("Thread deadlock detected, bad things may happen !!!");
            m_framethread->terminate(); //Thread didn't exit in time, probably deadlocked, terminate it!
            m_framethread->wait(); //Note: We have to wait again here!
            m_framethread=0;
        }
        //        //delete m_IDSFrameHandler;
        m_framethread=0;
    }

    return true;
}

bool IDSCamera::initThreadFrame(){

    if(stopThreadFrame()){
        m_framethread=new QThread();
        m_IDSFrameHandler= new IDSFrameEventHandler(0);
        m_IDSFrameHandler->setIDSCamera(this);
        m_IDSFrameHandler->moveToThread(m_framethread);


        connect(m_framethread,SIGNAL(started()),m_IDSFrameHandler,SLOT(run()));

        m_framethread->start(QThread::HighPriority);


    }
return true;


}

void IDSCamera::Finished()
{
    m_framethread=0;
}

void IDSCamera::GetImage(){

    if(m_RunMode==Snap){
        is_FreezeVideo(m_CameraHandler, IS_DONT_WAIT);
    }
}


void IDSCamera::setState(const CameraState &State)
{
    if (State==m_State) {
        return;
    }
    if (m_CameraHandler<0) {
        return;
    }

    try {

        if(State==Started){

            INT nRet = is_InitCamera (&m_CameraHandler, NULL);
            if (nRet != IS_SUCCESS)
            {
                qDebug()<<"Recturn code:"<<nRet;
                //Check if GigE uEye SE needs a new starter firmware
                if (nRet == IS_STARTER_FW_UPLOAD_NEEDED)
                {

                }
            }
            else{
                SENSORINFO sInfo;
                is_GetSensorInfo (m_CameraHandler, &sInfo);
                m_ImageWidth = sInfo.nMaxWidth;
                m_ImageHeigth = sInfo.nMaxHeight;




                nRet=is_SetDisplayMode (m_CameraHandler, IS_SET_DM_DIB);

                is_SetColorMode (m_CameraHandler, IS_CM_MONO8);

                UINT nSupportedBitDepths = 0;
                UINT nBitDepth=0;
                INT nRet = is_DeviceFeature(m_CameraHandler, IS_DEVICE_FEATURE_CMD_GET_SUPPORTED_SENSOR_BIT_DEPTHS,
                                            (void*)&nSupportedBitDepths, sizeof(nSupportedBitDepths));


                m_nBitsPerPixel=8;

                // memory initialization
                nRet= is_AllocImageMem (m_CameraHandler,
                                        m_ImageWidth,
                                        m_ImageHeigth,
                                        m_nBitsPerPixel,
                                        &m_pcImageMemory,
                                        &m_CameraMemoryId);
                nRet=is_SetImageMem (m_CameraHandler, m_pcImageMemory, m_CameraMemoryId);	// set memory active
                //is_SetImageMem()




#ifdef _WIN32

                Eventhandlers[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
                Eventhandlers[1] = CreateEvent(NULL, FALSE, FALSE, NULL);

                is_InitEvent(m_CameraHandler, Eventhandlers[0], IS_SET_EVENT_FRAME);
                is_EnableEvent(m_CameraHandler, IS_SET_EVENT_FRAME);
#endif

                initThreadFrame();

                InitializeSettings();

                nRet = is_ParameterSet(m_CameraHandler, IS_PARAMETERSET_CMD_LOAD_FILE, L"e:\\param.ini", NULL);

                m_State = Started;
            }
        }
        else{

            is_DisableEvent(m_CameraHandler, IS_SET_EVENT_FRAME);
            is_ExitEvent(m_CameraHandler, IS_SET_EVENT_FRAME);

            is_StopLiveVideo(m_CameraHandler,IS_WAIT);
            is_ExitCamera(m_CameraHandler);

            stopThreadFrame();
#ifdef _WIN32
            if(Eventhandlers[1]!=0)
                CloseHandle(Eventhandlers[1]);
#endif

            CleanupSettings();
            m_State = Stopped;
        }
    } catch (std::exception &e) {
        qDebug()<<"Except:"<<e.what();
    }



    emit CameraStateChaged(m_State);
}

CameraImageAOIModel *IDSCamera::ImageAOIs() const
{
    return m_ImageAOIs;
}





void IDSCamera::setRunMode(const CameraRunMode &RunMode)
{
    if(RunMode==m_RunMode) return;



    if(RunMode==Continuous){
        is_CaptureVideo(m_CameraHandler,IS_DONT_WAIT);
    }
    else{
        is_StopLiveVideo(m_CameraHandler,IS_WAIT);
    }


    m_RunMode = RunMode;
    emit CameraRunModeChaged(m_RunMode);
}
INT IDSCamera::ImageHeigth() const
{
    return m_ImageHeigth;
}
INT IDSCamera::ImageWidth() const
{
    return m_ImageWidth;
}

INT IDSCamera::CameraMemoryId()
{
    return m_CameraMemoryId;
}
HIDS IDSCamera::CameraHandler()
{
    return m_CameraHandler;
}

IDSCamera::CameraRunMode IDSCamera::RunMode() const
{
    return m_RunMode;
}


IDSCamera::CameraState IDSCamera::State() const
{
    return m_State;
}



CameraImageAOI::CameraImageAOI(QObject *parent, IMAGE_FORMAT_INFO ImageAOI)
{
    m_ImageAOI=ImageAOI;
}
IMAGE_FORMAT_INFO CameraImageAOI::ImageAOI() const
{
    return m_ImageAOI;
}




CameraImageAOIModel::CameraImageAOIModel(QObject *parent):
    QAbstractListModel(parent)
{

}

CameraImageAOIModel::~CameraImageAOIModel()
{
    RemoveAll();

}



void CameraImageAOIModel::AddImageAOI(CameraImageAOI *ImageAOI)
{
    beginInsertRows(QModelIndex(),m_ImageAOIs.count(),m_ImageAOIs.count());

    m_ImageAOIs.append(ImageAOI);

    endInsertRows();

}

void CameraImageAOIModel::RemoveImageAOI(CameraImageAOI *ImageAOI)
{
    int pos=m_ImageAOIs.indexOf(ImageAOI);
    beginRemoveRows(QModelIndex(),pos,pos);

    m_ImageAOIs.removeAt(pos);

    endRemoveRows();

}

void CameraImageAOIModel::RemoveAll()
{

   beginResetModel();

   m_ImageAOIs.clear();

   endResetModel();


}

//QList<CameraImageAOI *> CameraImageAOIModel::CameraImageAOI() const
//{
//    return m_ImageAOIs;
//}

//void CameraImageAOIModel::setCameraImageAOIs(const QList<CameraImageAOI *> &ImageAOIs)
//{
//    m_ImageAOIs = ImageAOIs;
//}



int CameraImageAOIModel::rowCount(const QModelIndex &parent) const
{
    int ct=m_ImageAOIs.count();
    return ct;
}


QVariant CameraImageAOIModel::data(const QModelIndex &index, int role) const
{


    // Check that the index is valid and within the correct range first:
    if (!index.isValid())
        return QVariant();

    if (index.row() >= m_ImageAOIs.count())
        return QVariant();

    if (role == Qt::DisplayRole) {
        CameraImageAOI *selected = m_ImageAOIs.at(index.row());
        QString ret=QString("%1 x %2").arg(selected->ImageAOI().nWidth).arg(selected->ImageAOI().nHeight);
        return QVariant(ret);
    }
//    else if(role == Qt::UserRole){
//        IDSCamera *cam=m_Cameras[(int)m_ListCameras->uci[index.row()].dwCameraID];
//        return QVariant::fromValue<IDSCamera*>(cam);
//    }
    else
        return QVariant();
}
