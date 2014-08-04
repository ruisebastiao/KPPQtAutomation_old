#include "kpplineedit.h"
#include "qtooltip.h"
#include "QMouseEvent"
#include "qapplication.h"

KPPLineEdit::KPPLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
}


void KPPLineEdit::changeEvent(QEvent *)
{
    setToolTip(text());
}


void KPPLineEdit::mousePressEvent(QMouseEvent *e)
{


    QLineEdit::mousePressEvent(e);

}


void KPPLineEdit::mouseMoveEvent(QMouseEvent *e)
{
    if(!text().isEmpty()){
        QToolTip::showText(e->globalPos(),text(),this);
    }
    QLineEdit::mouseMoveEvent(e);
}


void KPPLineEdit::focusInEvent(QFocusEvent *e)
{

        QLineEdit::focusInEvent(e);

}

