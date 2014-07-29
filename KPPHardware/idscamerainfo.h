#ifndef IDSCAMERAINFO_H
#define IDSCAMERAINFO_H

#include "kpphardware_global.h"
#include "camerainfo.h"
#include "idscamera.h"

namespace IDS {

class KPPHARDWARESHARED_EXPORT IDSCameraInfo:public CameraInfo
{
    Q_OBJECT

public:

    explicit IDSCameraInfo(QObject *parent = 0);
    void InitCamera(int CameraId);

    //static void setCameras(UEYE_CAMERA_LIST *Cameras);

private:

    QHash<int,IDSCamera*> m_Cameras;

    UEYE_CAMERA_LIST* m_ListCameras;
    void UpdateCamerasList();


public:
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int,IDSCamera *> Cameras() const;

};


//HIDS	m_hCam;			// handle to camera
//HWND	m_hWndDisplay;	// handle to diplay window
//INT		m_Ret;			// return value of uEye SDK functions
//INT		m_nColorMode;	// Y8/RGB16/RGB24/REG32
//INT		m_nBitsPerPixel;// number of bits needed store one pixel
//INT		m_nSizeX;		// width of video
//INT		m_nSizeY;		// height of video
//INT		m_lMemoryId;	// grabber memory - buffer ID
//char*	m_pcImageMemory;// grabber memory - pointer to buffer
//INT     m_nRenderMode;  // render  mode
//SENSORINFO m_sInfo;	    // sensor information struct

}
#endif // IDSCAMERAINFO_H
