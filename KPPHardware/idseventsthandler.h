#ifndef IDSEVENTSHANDLER_H
#define IDSEVENTSHANDLER_H

#include "kpphardware_global.h"
#include <QThread>
#include <uEye.h>
#include "qmutex.h"
#include "qwaitcondition.h"
#include "qimage.h"
#include "qpixmap.h"

namespace IDS {

class KPPHARDWARESHARED_EXPORT IDSCamera;

class KPPHARDWARESHARED_EXPORT IDSFrameEventHandler : public QObject
{
    Q_OBJECT
public:
    explicit IDSFrameEventHandler(QObject *parent = 0);
    ~IDSFrameEventHandler();
    void Abort();


    void setIDSCamera(IDSCamera *parentIDSCamera);

private:
    //    HANDLE m_eventHandler;
    IDSCamera* m_IDSCamera;
    bool m_stop;
    QPixmap newpixmap;
//    QMutexLocker locker;
//    QMutex mutex;
//    QWaitCondition cond;
signals:

public slots:
    void run();


protected:

};

}

#endif // IDSEVENTSHANDLER_H
