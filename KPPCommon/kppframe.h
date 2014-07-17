#ifndef KPPFRAME_H
#define KPPFRAME_H

#include <QWidget>
#include "qframe.h"
#include "qeasingcurve.h"
#include "kppcommon_global.h"

class KPPCOMMONSHARED_EXPORT KPPFrame : public QFrame
{
    Q_OBJECT
    void AdjustContents(int startValue, int finalValue, QEasingCurve animStyle=QEasingCurve::InCirc);
public:
    explicit KPPFrame(QWidget *parent = 0);

    void SetMaxval(int FinalValue);

    bool visible() const;
    void setFrameVisible(bool visible);

private:
    int m_finalVal;
    bool m_visible;
signals:

public slots:


    // QWidget interface
protected:
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *);
private slots:
    void AnimationFinished();
};

#endif // KPPFRAME_H
