#ifndef VISIONTREEVIEW_H
#define VISIONTREEVIEW_H

#include "kppvision_global.h"
#include <QTreeWidget>
#include <QPushButton>
#include "kppadjustablelistview.h"
#include "kppvision.h"
#include "kppvisionlist.h"
#include "kpptreewidgetitem.h"


class KPPVISIONSHARED_EXPORT VisionTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit VisionTreeWidget(QWidget *parent = 0);




    void AddVisionProjectsModel(Vision::KPPVisionList<Vision::KPPVision> *VisionProjects);
private:
     QTreeWidgetItem *projectsitem;
     QPushButton *bt_project;
     QTreeWidgetItem* projectssubitem;
     KPPAdjustableListView* list_projects;

     KPPTreeWidgetItem *RequestsItem;
     QPushButton *bt_request;
     QTreeWidgetItem* RequestSubItem;
     KPPAdjustableListView* list_requests;

    QTimer *updatelayouttimer;
    Vision::KPPVision* m_selectedProject;
    void setSelectedProject(Vision::KPPVision *value);
protected:



signals:

public slots:
     void bt_projectClicked();
private slots:


     void VisionProjectsdataChanged(QModelIndex, QModelIndex);
     void VisionProjectsrowsAboutToBeInserted(QModelIndex modelindex, int start, int end);
     void VisionProjectsrowsInserted(QModelIndex modelindex, int start, int end);  
     void VisionProjectsrowsAboutToBeRemoved(QModelIndex modelindex, int start, int end);
     void VisionProjectsrowsRemoved(QModelIndex modelindex, int start, int end);
     void bt_RequestClicked();

     void SelectionChanged(QItemSelection, QItemSelection);
     void RequestsrowsAboutToBeInserted(QModelIndex modelindex, int start, int end);
     void RequestsrowsInserted(QModelIndex modelindex, int start, int end);
public slots:





     // QTreeView interface
protected:
   //  void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;

     // QTreeView interface
protected:
    // void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
};


#endif // SIDETREEVIEW_H
