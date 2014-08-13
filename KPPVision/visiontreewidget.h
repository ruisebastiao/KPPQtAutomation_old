#ifndef VISIONTREEVIEW_H
#define VISIONTREEVIEW_H

#include "kppvision_global.h"
#include <QTreeWidget>
#include <QPushButton>
#include "kppadjustablelistview.h"
#include "kppvision.h"
#include "kppvisionlist.h"
#include "kpptreewidgetitem.h"
#include "kpptreepushbutton.h"
#include "requestmenu.h"
#include "inspectionmenu.h"

class KPPVISIONSHARED_EXPORT VisionTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit VisionTreeWidget(QWidget *parent = 0);




    void AddVisionProjectsModel(Vision::KPPVisionList<Vision::KPPVision> *VisionProjects);
private:
    QTimer *updatelayouttimer;

    QTreeWidgetItem *Projectsitem;
    QPushButton *bt_Projects;
    QTreeWidgetItem* ProjectsSubItem;
    KPPAdjustableListView* list_Projects;

    Vision::KPPVision* m_SelectedProject;
    void setSelectedProject(Vision::KPPVision* value);


    KPPTreeWidgetItem *RequestsItem;
    KPPRootTreePushButton *bt_Request;
    QTreeWidgetItem* RequestsSubItem;
    KPPAdjustableListView* list_Requests;



    void setSelectedRequest(Vision::Request* value);


    KPPTreeWidgetItem *InspectionsItem;
    KPPRootTreePushButton *bt_Inspections;
    QTreeWidgetItem* InspectionsSubItem;
    KPPAdjustableListView* list_Inspections;


    void setSelectedInspection(Vision::Inspection* value);


    KPPTreeWidgetItem *ROIItem;
    KPPRootTreePushButton *bt_ROI;
    QTreeWidgetItem* ROISubItem;
    KPPAdjustableListView* list_ROIS;


    void setSelectedROI(Vision::ROI* value);



    RequestMenu *m_requestmenu;
    InspectionMenu *m_inspectionmenu;

protected:



signals:
    void ListSelectionChanged(QObject*);
public slots:
    void bt_projectClicked();
private slots:


    void VisionProjectsDataChanged(QModelIndex, QModelIndex);
    void VisionProjectsRowsAboutToBeInserted(QModelIndex modelindex, int start, int end);
    void VisionProjectsRowsInserted(QModelIndex modelindex, int start, int end);
    void VisionProjectsRowsAboutToBeRemoved(QModelIndex modelindex, int start, int end);
    void VisionProjectsRowsRemoved(QModelIndex modelindex, int start, int end);
    void bt_RequestClicked();

    void SelectionChanged(QItemSelection, QItemSelection);
    void RequestsRowsAboutToBeInserted(QModelIndex modelindex, int start, int end);
    void RequestsRowsInserted(QModelIndex modelindex, int start, int end);
    void InspectionrowsAboutToBeRemoved(QModelIndex modelindex, int start, int end);
    void InspectionsRowsRemoved(QModelIndex modelindex, int start, int end);
    void InspectionrowsAboutToBeInserted(QModelIndex modelindex, int start, int end);
    void InspectionrowsRowsInserted(QModelIndex modelindex, int start, int end);
    void bt_InspectionsClicked();
    void RequestsRowsRemoved(QModelIndex modelindex, int start, int end);

    void ListItemPressed(QModelIndex);
    void ListItemSwipeRight();

    void bt_ROIClicked();
    void ROIrowsAboutToBeInserted(QModelIndex modelindex, int start, int end);
    void ROIRowsInserted(QModelIndex modelindex, int start, int end);
    void ROIRowsRemoved(QModelIndex modelindex, int start, int end);

    //void ROIPressedSlot(ROI* roi);

    void SceneSelectionChanged();
public slots:





    // QTreeView interface

protected:
    //  void drawRow(QPainter *painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;

    // QTreeView interface
protected:
    // void drawBranches(QPainter *painter, const QRect &rect, const QModelIndex &index) const;
};


#endif // SIDETREEVIEW_H
