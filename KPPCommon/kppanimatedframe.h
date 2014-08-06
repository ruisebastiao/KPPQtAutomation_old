#ifndef KPPANIMATEDFRAME_H
#define KPPANIMATEDFRAME_H

#include <QFrame>
#include "kppcommon_global.h"
#include "qpropertyanimation.h"
#include "qparallelanimationgroup.h"

namespace Ui {
class KPPCOMMONSHARED_EXPORT KPPAnimatedFrame;
}

class KPPCOMMONSHARED_EXPORT KPPAnimatedFrame : public QFrame
{
    Q_OBJECT

public:
    explicit KPPAnimatedFrame(QWidget *parent = 0, Qt::WindowFlags f = 0,QRect alignmentRect=QRect());
    ~KPPAnimatedFrame();

private:
    Ui::KPPAnimatedFrame *ui;
    QRect m_alignmentRect;
    QPropertyAnimation * animate_opacity;
    QPropertyAnimation *animate_width ;
    QParallelAnimationGroup* animation;
    bool m_visible;
    // QWidget interface
public slots:
    void setVisible(bool visible);

    // QWidget interface
protected:
    void leaveEvent(QEvent *);

    // QWidget interface
protected:
    void focusInEvent(QFocusEvent *);
    void focusOutEvent(QFocusEvent *);
private slots:
    void AnimationFinished();
};

#endif // KPPANIMATEDFRAME_H
