#ifndef KPPLINEEDIT_H
#define KPPLINEEDIT_H

#include <qlineedit.h>
#include "kppcommon_global.h"

class KPPCOMMONSHARED_EXPORT KPPLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit KPPLineEdit(QWidget *parent = 0);

signals:

public slots:


    // QWidget interface
protected:
    void changeEvent(QEvent *);

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *);

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *);

    // QWidget interface
protected:
    void focusInEvent(QFocusEvent *);


};

#endif // KPPLINEEDIT_H
