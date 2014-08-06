#ifndef KPPANIMATEDFRAME_H
#define KPPANIMATEDFRAME_H

#include <QFrame>
#include "kppcommon_global.h"
#include "qpropertyanimation.h"
#include "qparallelanimationgroup.h"
#include"qsequentialanimationgroup.h"

class KPPCOMMONSHARED_EXPORT KPPAnimatedFrame : public QFrame
{
    Q_OBJECT

public:
    explicit KPPAnimatedFrame(QWidget *parent = 0);
    ~KPPAnimatedFrame();

    QRect AlignmentRect() const;
    void setAlignmentRect(const QRect &alignmentRect);

private:

    QRect m_alignmentRect;
    QPropertyAnimation * animate_opacity;
    QPropertyAnimation *animate_geometry ;
    QPropertyAnimation *animate_finalgeometry ;
    QParallelAnimationGroup* parallel_animations;
    QSequentialAnimationGroup* seq_animations;
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

    // QWidget interface
protected:
    void hideEvent(QHideEvent *);
};

#endif // KPPANIMATEDFRAME_H
