#ifndef IDSCAMERA_H
#define IDSCAMERA_H

#include "kpphardware_global.h"
#include "QObject"
#include "QWindow"
#include <uEye.h>
#include "idseventsthandler.h"
#include "QThread"
#include "QAbstractItemModel"
#include "idscamerainfo.h"


namespace IDS {

class KPPHARDWARESHARED_EXPORT CameraImageAOIModel;

class KPPHARDWARESHARED_EXPORT IDSCamera:public QObject
{

    Q_ENUMS(CameraState)
    Q_ENUMS(CameraRunMode)
    Q_OBJECT
public:
    enum CameraState {
        Started = 0x1,
        Stopped = 0x2
    };

    enum CameraRunMode {
        Continuous = 0x1,
        Snap = 0x2
    };
    explicit IDSCamera(QObject *parent=0, int cameraID=-1, QWidget *parentWidget=0);
    ~IDSCamera();


    void GetImage();



    INT ImageHeigth() const;


    INT ImageWidth() const;




    INT CameraMemoryId();


    //HANDLE  EventHandlers[2];
    HANDLE Eventhandlers[2];


    HIDS CameraHandler();


    CameraRunMode RunMode() const;
    void setRunMode(const CameraRunMode &RunMode);

    CameraState State() const;
    void setState(const CameraState &State);

    //IDSCameraConfig *CameraConfigWindow() const;


    CameraImageAOIModel *ImageAOIs() const;


private:
    HIDS	m_CameraHandler;			// handle to camera
    //HWND	m_hWndDisplay;	// handle to diplay window
    //INT		m_Ret;			// return value of uEye SDK functions
    //INT		m_nColorMode;	// Y8/RGB16/RGB24/REG32
    INT		m_nBitsPerPixel;// number of bits needed store one pixel
    INT		m_ImageWidth;		// width of video
    INT		m_ImageHeigth;		// height of video
    INT		m_CameraMemoryId;	// grabber memory - buffer ID
    char*	m_pcImageMemory;// grabber memory - pointer to buffer
    INT     m_nRenderMode;  // render  mode
    SENSORINFO m_sInfo;	    // sensor information struct

    CameraRunMode m_RunMode;
    CameraState m_State;

    QThread *m_framethread;
    IDSFrameEventHandler *m_IDSFrameHandler;

    //IDSCameraConfig *m_CameraConfigWindow;
    IMAGE_FORMAT_LIST* m_formatsAvaible;
    CameraImageAOIModel *m_ImageAOIs;

    bool stopThreadFrame();
    bool initThreadFrame();
    void InitializeSettings();
    void CleanupSettings();
signals:
    void CameraStateChaged(IDSCamera::CameraState NewState);    
    void CameraRunModeChaged(IDSCamera::CameraRunMode NewRunMode);
    void ImageAvaibleSignal(QPixmap);

private slots:
    void Finished();
};

//}

class KPPHARDWARESHARED_EXPORT CameraImageAOI:public QObject{
    Q_OBJECT

public:
    explicit CameraImageAOI(QObject *parent, IMAGE_FORMAT_INFO ImageAOI);
    IMAGE_FORMAT_INFO ImageAOI() const;


private:
    IMAGE_FORMAT_INFO m_ImageAOI;
};

class KPPHARDWARESHARED_EXPORT CameraImageAOIModel:public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CameraImageAOIModel(QObject *parent);
    ~CameraImageAOIModel();
    void AddImageAOI(CameraImageAOI* ImageAOI);
    void RemoveImageAOI(CameraImageAOI* ImageAOI);
    void RemoveAll();



private:
    QList<CameraImageAOI*> m_ImageAOIs;

    // QAbstractItemModel interface
public:

    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
};

}
#endif // IDSCAMERA_H
