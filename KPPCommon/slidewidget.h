#ifndef SLIDEWIDGET_H
#define SLIDEWIDGET_H
#include "kppcommon_global.h"
#include <QWidget>

class KPPCOMMONSHARED_EXPORT SlideWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SlideWidget(QWidget *parent = 0);
    bool Displayed() const;
    void setDisplayed(bool Displayed);

private:
    bool m_displayed;

signals:

public slots:

};

#endif // SLIDEWIDGET_H
