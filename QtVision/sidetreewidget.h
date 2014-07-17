#ifndef SIDETREEVIEW_H
#define SIDETREEVIEW_H

#include <QTreeWidget>
#include <QPushButton>
#include "kppadjustablelistview.h"

class QtCategoryButton;

class SideTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit SideTreeWidget(QWidget *parent = 0);

    KPPAdjustableListView *getListViewProjects() const;


    KPPAdjustableListView *getlistViewInspections() const;


private:
    KPPAdjustableListView *m_listViewProjects;
    KPPAdjustableListView *m_listViewInspections;
    QtCategoryButton* bt_Inspections;
    QTreeWidgetItem* pContainerInspections;
    QTreeWidgetItem* pCategoryInspections;
    QTreeWidgetItem* pCategoryProjects;
protected:

    //void itemClicked(QTreeWidgetItem *item, int column);

signals:

private slots:

   void ProjectSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
public slots:

    void clicked(bool checked = false);
    void InspectionsBtclicked();
    void OpenBtClicked();

};

class QtCategoryButton : public QPushButton
{
    Q_OBJECT
public:
    QtCategoryButton(const QString& a_Text, QTreeWidget* a_pParent,
        QTreeWidgetItem* a_pItem);

private slots:
    void ButtonPressed();
    void collapsed(QModelIndex);

private:
    QTreeWidgetItem* m_pItem;
    QTreeWidget * m_TreeWidget;
    bool doexpand;
};

#endif // SIDETREEVIEW_H
