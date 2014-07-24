#ifndef KPPPUSHBUTTON_H
#define KPPPUSHBUTTON_H

#include "kppcommon_global.h"
#include <QPushButton>
#include "qpropertyanimation.h"
#include "qstyleoption.h"
#include "qpainter.h"



class KPPCOMMONSHARED_EXPORT KPPPushbutton : public QPushButton
{    
    Q_OBJECT
public:
    explicit KPPPushbutton(QWidget *parent = 0);

    virtual void paintEvent(QPaintEvent *);
    void	setVisible ( bool visible );


private:
    bool ishover,resizing,m_visible;
    int defaultSize;
    QPropertyAnimation *animation1;
signals:

private slots:


    void AnimationFinished();

public slots:


    // QWidget interface
protected:

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);


    // QAbstractButton interface
protected:


    // QWidget interface
protected:
    void showEvent(QShowEvent *);
};


#endif // KPPPUSHBUTTON_H
