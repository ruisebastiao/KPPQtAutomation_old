#ifndef VISIONTREEVIEW_H
#define VISIONTREEVIEW_H

#include "kppvision_global.h"
#include <QTreeWidget>
#include <QPushButton>
#include "kppadjustablelistview.h"
#include "kppvision.h"
#include "kpptreewidgetitem.h"


class KPPVISIONSHARED_EXPORT VisionTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit VisionTreeWidget(QWidget *parent = 0);




    void AddVisionProjectsModel(Vision::ProjectsList *VisionProjects);
private:
     QTreeWidgetItem *projectsitem;
     QPushButton *bt_project;
     QTreeWidgetItem* projectssubitem;
     KPPAdjustableListView* list_projects;

     KPPTreeWidgetItem *inspectionsitem;
     QPushButton *bt_inspect;
     QTreeWidgetItem* inspectionssubitem;
     KPPAdjustableListView* list_inspections;

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
     void bt_InspectionClicked();

     void SelectionChanged(QItemSelection, QItemSelection);
     void InspectionsrowsAboutToBeInserted(QModelIndex modelindex, int start, int end);
     void InspectionsrowsInserted(QModelIndex modelindex, int start, int end);
public slots:





     // QTreeView interface
protected:
   //  void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;

     // QTreeView interface
protected:
    // void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
};


#endif // SIDETREEVIEW_H
