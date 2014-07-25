#ifndef KPPROOTTREEPUSHBUTTON_H
#define KPPROOTTREEPUSHBUTTON_H

#include "kppcommon_global.h"
#include <QPushButton>
#include "QTreeWidgetItem"

class KPPCOMMONSHARED_EXPORT KPPRootTreePushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit KPPRootTreePushButton(QString text, QTreeWidgetItem *widgetitem, QWidget *parent = 0);
    void setText(const QString &text);
    QTreeWidgetItem *widgetItem() const;
    void setWidgetItem(QTreeWidgetItem *widgetItem);

private:
    QTreeWidgetItem *m_widgetItem;
signals:

public slots:

private slots:
    void ButtonClickedSlot();

};

#endif // KPPROOTTREEPUSHBUTTON_H
