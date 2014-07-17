#include "sidetreewidget.h"
#include "QBoxLayout"
#include "QDebug"
#include "kppvision.h"
#include "settings.h"


class QAdjustableTreeItemDelegate : public QStyledItemDelegate
{
public:
    QAdjustableTreeItemDelegate(QObject* parent = 0)
        : QStyledItemDelegate(parent)
    {


    }

    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
    {
        return QStyledItemDelegate::sizeHint(option,index);

        //         QSize s;
        //            s = QSize(option.decorationSize.width(), option.decorationSize.height());
        //            //if(currentIndex == index.row())
        //            //{
        //                s.setHeight(option.decorationSize.height()*2);
        //            //}
        //            return s;
    }
};


//class QTreeWidgetItemAdjustable : public QTreeWidgetItem
//{
//public:
//    QTreeWidgetItemAdjustable(QObject* parent = 0)
//        : QTreeWidgetItem()
//    {


//    }


//};


class QFrameAdjustable : public QFrame
{
public:
    QFrameAdjustable(QWidget* parent = 0)
        : QFrame(parent)
    {


    }



    // QWidget interface
public:
    QSize sizeHint() const
    {
        //layout()->children()
        //qDebug()<<childrenRegion();
        //return QWidget::sizeHint();
        //return QSize(parentWidget()->width(),layout()->->contentsRect().height());
    }

    //     // QWidget interface
    //public:
    //     QSize minimumSizeHint() const
    //     {
    //         return QSize(size().width(),50);
    //     }
};

SideTreeWidget::SideTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setRootIsDecorated(false);
    setIndentation(0);






    //Projects Section
    {
        pCategoryProjects = new QTreeWidgetItem();

        addTopLevelItem(pCategoryProjects);

        QtCategoryButton* bt_Projects=new QtCategoryButton(tr("Project"),this, pCategoryProjects);
        //bt_Projects->setFixedHeight(35);
        connect(bt_Projects,SIGNAL(clicked()),this,SLOT(clicked()));

        setItemWidget(pCategoryProjects, 0, bt_Projects);

        QFrame* pFrameProjects = new QFrame(this);
        /*
        pFrameProjects->setStyleSheet("border-width: 1px;\
                                      border-style: solid;\
                border-color: black;");
*/
        QBoxLayout* pLayoutProjects = new QVBoxLayout(pFrameProjects);

        QPushButton *bt_open=new QPushButton(tr("Open"));
        pLayoutProjects->addWidget(bt_open);

        connect(bt_open,SIGNAL(clicked()),this,SLOT(OpenBtClicked()));


        m_listViewProjects=new KPPAdjustableListView(pFrameProjects);
        connect(m_listViewProjects,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(ProjectSelectionChanged(QItemSelection,QItemSelection)));
        pLayoutProjects->addWidget(m_listViewProjects);


        QPushButton *save_bt= new QPushButton(tr("Save"));
        pLayoutProjects->addWidget(save_bt);




        QTreeWidgetItem* pContainerProjects = new QTreeWidgetItem();

        //  pFrame1->setMaximumHeight(450);
        pContainerProjects->setDisabled(true);
        pCategoryProjects->addChild(pContainerProjects);
        setItemWidget(pContainerProjects, 0, pFrameProjects);
    }




    //Inspections Section
    {
        pCategoryInspections = new QTreeWidgetItem();

        addTopLevelItem(pCategoryInspections);

        bt_Inspections=new QtCategoryButton(tr("Inspections"),this, pCategoryInspections);

        bt_Inspections->setEnabled(false);

        connect(bt_Inspections,SIGNAL(clicked()),this,SLOT(clicked()));

        setItemWidget(pCategoryInspections, 0, bt_Inspections);

        QFrame* pFrameInspections = new QFrame(this);
        /*
        pFrameInspections->setStyleSheet("border-width: 1px;\
                                      border-style: solid;\
                border-color: black;");
                */

        QBoxLayout* pLayoutInspection = new QVBoxLayout(pFrameInspections);

        m_listViewInspections=new KPPAdjustableListView(pFrameInspections);

        pLayoutInspection->addWidget(m_listViewInspections);

        pContainerInspections = new QTreeWidgetItem();

        //  pFrame1->setMaximumHeight(450);
        pContainerInspections->setDisabled(true);
        pCategoryInspections->addChild(pContainerInspections);
        setItemWidget(pContainerInspections, 0, pFrameInspections);
    }



}
KPPAdjustableListView *SideTreeWidget::getListViewProjects() const
{
    return m_listViewProjects;
}
KPPAdjustableListView *SideTreeWidget::getlistViewInspections() const
{
    return m_listViewInspections;
}

void SideTreeWidget::ProjectSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    if (selected.count()>0) {

        bt_Inspections->setEnabled(true);
        pCategoryInspections ->setExpanded(true);
    }
    else {
        bt_Inspections->setEnabled(false);
        pCategoryInspections->setExpanded(false);
    }
}



void SideTreeWidget::clicked(bool checked){

    if (checked) {

    }
}


void SideTreeWidget::InspectionsBtclicked()
{
    QItemSelectionModel *itemselected=m_listViewProjects->selectionModel();
    if(itemselected->selectedIndexes().count()>0){
        QString projName= itemselected->selectedIndexes().at(0).data().toString();
        Settings::AppSettings->Projects()->setSelectedPoject(Settings::AppSettings->Projects()->getProject(projName));
    }
    //
}

void SideTreeWidget::OpenBtClicked()
{


}


QtCategoryButton::QtCategoryButton( const QString& a_Text,
                                    QTreeWidget* a_pParent, QTreeWidgetItem* a_pItem )
    : QPushButton(a_Text, a_pParent)
    , m_pItem(a_pItem)
    ,m_TreeWidget(a_pParent)
    ,doexpand(false)
{
    connect(this, SIGNAL(pressed()), this, SLOT(ButtonPressed()));
    connect(a_pParent, SIGNAL(collapsed(QModelIndex)), this, SLOT(collapsed(QModelIndex)));
}

void QtCategoryButton::ButtonPressed()
{
    //    doexpand=true;
    //    if(m_TreeWidget->isExpanded(QModelIndex())==false)
    //        m_TreeWidget->collapseAll();
    //   else
    m_pItem->setExpanded( !m_pItem->isExpanded() );


}

void QtCategoryButton::collapsed(QModelIndex)
{
    //    if(doexpand){
    //        doexpand=false;
    //        m_pItem->setExpanded( !m_pItem->isExpanded() );
    //    }
}
