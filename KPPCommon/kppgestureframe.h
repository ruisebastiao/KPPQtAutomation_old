#ifndef KPPGESTUREFRAME_H
#define KPPGESTUREFRAME_H

#include "kppcommon_global.h"
#include <QWidget>
#include <QFrame>

class KPPCOMMONSHARED_EXPORT KPPGestureFrame : public QFrame
{
    Q_OBJECT
public:
    explicit KPPGestureFrame(QWidget *parent = 0);

signals:

public slots:


    // QObject interface
public:
    //bool event(QEvent *pEvent);
};

#endif // KPPGESTUREFRAME_H
