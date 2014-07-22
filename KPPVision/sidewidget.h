#ifndef SIDEWIDGET_H
#define SIDEWIDGET_H

#include "kppvision_global.h"
#include <QWidget>
#include <QPropertyAnimation>
#include <QStyleOption>

#include <QPainter>


class KPPVISIONSHARED_EXPORT SideWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(State)

public:
    enum State {
        Opened=0x00,
        Closed=0x01
    };

    explicit SideWidget(QWidget *parent = 0);

    State getMenuState() const;
    void setMenuState(const State &value);

    SideWidget::State toogleMenuState();


private:
    State menuState;
    bool lostFocustoChild;
protected:
    void paintEvent(QPaintEvent *);

signals:

public slots:


};

#endif // SLIDEWIDGET_H
