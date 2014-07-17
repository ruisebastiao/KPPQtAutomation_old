#include "idseventsthandler.h"
#include "qdebug.h"
#include "idscamera.h"

using namespace IDS;

IDSFrameEventHandler::IDSFrameEventHandler(QObject *parent) :
    QObject(parent)
{
    m_stop=false;    

}

void IDSFrameEventHandler::Abort()
{

    m_stop=true;

}


void IDSFrameEventHandler::run()
{
//TODO Prepare for linux
#ifdef _WIN32
    while (!m_stop) {

        //DWORD dwRet = WaitForSingleObject(m_IDSCamera->Eventhandlers, 1000);
        DWORD dwRet=WaitForMultipleObjects(2,m_IDSCamera->Eventhandlers, FALSE ,INFINITE );
        if (dwRet == WAIT_OBJECT_0+1)
        {
           break;
        }
        else if (dwRet == WAIT_OBJECT_0)
        {

           // qDebug()<<"Image Frame";
            //emi

          /* event signalled */
            char* mem;
            INT memid=m_IDSCamera->CameraMemoryId();
            is_GetActiveImageMem(m_IDSCamera->CameraHandler(),&mem,&memid);
            //mutex.lock();

            QImage img=QImage((unsigned char*)mem, m_IDSCamera->ImageWidth(), m_IDSCamera->ImageHeigth(), QImage::Format_Indexed8 );
            //newpixmap.fromImage(img);
            //emit m_IDSCamera->ImageAvaibleSignal(((unsigned char*)mem, m_IDSCamera->ImageWidth(), m_IDSCamera->ImageHeigth(), QImage::Format_Indexed8 ));
            emit m_IDSCamera->ImageAvaibleSignal(QPixmap::fromImage(img));

            //cond.wait(&mutex);
            //mutex.unlock();
        }
    }

    deleteLater();
#endif
}

void IDSFrameEventHandler::setIDSCamera(IDSCamera *parentIDSCamera)
{
    m_IDSCamera = parentIDSCamera;
    newpixmap= QPixmap(m_IDSCamera->ImageWidth(),m_IDSCamera->ImageHeigth());
}


//void IDSEventsThread::signalImageAvaible()
//   {
//      // wake up the Server objects
//      mpWaitCondition->wakeOne();
//      //mpWaitCondition->wakeAll();
//      qDebug() << "client  called wake all,.thread:" << QThread::currentThreadId();
//   }


IDSFrameEventHandler::~IDSFrameEventHandler()
{
    m_stop=true;
}
