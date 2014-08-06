#ifndef KPPSWIPEBUTTON_H
#define KPPSWIPEBUTTON_H

#include <QPushButton>
#include "kppcommon_global.h"
#include "QSwipeGesture"

class KPPCOMMONSHARED_EXPORT KPPSwipeButton :public QPushButton
{
    Q_OBJECT

public:
    explicit KPPSwipeButton(QWidget *parent = 0);

signals:

public slots:
private:


};

#endif // KPPSWIPEBUTTON_H
