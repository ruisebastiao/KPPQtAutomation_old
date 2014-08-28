#ifndef KPPROOTTREEPUSHBUTTON_H
#define KPPROOTTREEPUSHBUTTON_H

#include "kppcommon_global.h"
#include <QPushButton>
#include "QTreeWidgetItem"
#include "qgesture.h"

class KPPCOMMONSHARED_EXPORT KPPRootTreePushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit KPPRootTreePushButton(QString text, QTreeWidgetItem *widgetitem, QWidget *parent = 0);
    void setText(const QString &text);
    QTreeWidgetItem *widgetItem() const;
    void setWidgetItem(QTreeWidgetItem *widgetItem);

    bool event(QEvent *event);

private:
    QTreeWidgetItem *m_widgetItem;
    bool gestureEvent(QGestureEvent *event);
    bool swipeTriggered(QSwipeGesture *pSwipe);
    void setExpandOthers(bool value);
    bool m_WasGesture;
signals:

public slots:
    void SetExpandItem(bool value);
private slots:
    void ButtonClickedSlot();

};

#endif // KPPROOTTREEPUSHBUTTON_H
