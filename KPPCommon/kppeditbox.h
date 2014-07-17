#ifndef KPPEDITBOX_H
#define KPPEDITBOX_H

#include <QWidget>
#include "kppcommon_global.h"
#include "QLineEdit"


class KPPCOMMONSHARED_EXPORT KPPEditBox : public QLineEdit
{
    Q_OBJECT
public:
    explicit KPPEditBox(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
   // void paintEvent(QPaintEvent *);
};

#endif // KPPEDITBOX_H
