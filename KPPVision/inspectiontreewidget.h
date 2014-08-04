#ifndef INSPECTIONTREEWIDGET_H
#define INSPECTIONTREEWIDGET_H

#include "kppvision_global.h"
#include <QTreeWidget>
#include "capturesource.h"
#include "qlabel.h"
#include "qcombobox.h"
#include "QHeaderView"
#include "qpushbutton.h"
#include "QVBoxLayout"
#include "kpptreepushbutton.h"
#include "inspection.h"
#include "qpainter.h"
#include "qstyleditemdelegate.h"

class KPPVISIONSHARED_EXPORT InspectionTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit InspectionTreeWidget(QWidget *parent = 0);
    void setInspection(Vision::Inspection *selectedInsp);
   // ~InspectionTreeWidget();


private:
    QComboBox* cb_capturesource;
    Vision::Inspection* m_selectedInsp;

    QVBoxLayout *layout_sourcename;
    QVBoxLayout *layout_sourcesettings;


    QFrame *frame_sourcename;
    QFrame *frame_sourcesettings;

    QTreeWidgetItem *item_sourcetype;
    QTreeWidgetItem *item_sourcename;
    QTreeWidgetItem *item_sourcesettings;





     KPPRootTreePushButton *bt_sourcename;
     KPPRootTreePushButton *bt_type;

     void Initialize_Trees();
     void UpdateSourceType();
signals:

public slots:

private slots:
    void cbCapturecurrentIndexChanged(QString);


public:
   // QRect visualRect(const QModelIndex &index) const;

    // QAbstractItemView interface
public:

    void DoShow();
    void DoHide();
};


#endif // INSPECTIONTREEWIDGET_H
