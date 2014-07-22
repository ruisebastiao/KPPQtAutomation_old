#include "visiontreewidget.h"
#include "QBoxLayout"
#include "QDebug"
#include "kppvision.h"
#include "settings.h"
#include "kppadjustablelistview.h"

using namespace Vision;


VisionTreeWidget::VisionTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setRootIsDecorated(false);
    setHeaderHidden(true);
    setIndentation(0);
    setAnimated(true);


    updatelayouttimer= new QTimer(this);
    updatelayouttimer->setSingleShot(true);
    updatelayouttimer->setInterval(150);
    connect(updatelayouttimer, SIGNAL(timeout()), this, SLOT(doItemsLayout()));




    projectsitem=new KPPTreeWidgetItem(0);
    bt_project= new QPushButton(this);
    connect(bt_project,SIGNAL(clicked()),this,SLOT(bt_projectClicked()));
    bt_project->setText(tr("Projects"));
    bt_project->setAutoFillBackground(true);
    addTopLevelItem(projectsitem);
    this->setItemWidget(projectsitem,0,bt_project);

    inspectionsitem=new KPPTreeWidgetItem(0);
    bt_inspect= new QPushButton(this);
    connect(bt_inspect,SIGNAL(clicked()),this,SLOT(bt_InspectionClicked()));
    bt_inspect->setText(tr("Inspections"));
    bt_inspect->setEnabled(false);

    addTopLevelItem(inspectionsitem);
    bt_inspect->setAutoFillBackground(true);
    this->setItemWidget(inspectionsitem,0,bt_inspect);


    m_selectedProject=0;



}


void VisionTreeWidget::VisionProjectsdataChanged(QModelIndex start,QModelIndex end){

    list_projects->repaint();
}

void VisionTreeWidget::VisionProjectsrowsAboutToBeRemoved(QModelIndex modelindex,int start,int end){

}


void VisionTreeWidget::VisionProjectsrowsRemoved(QModelIndex modelindex,int start,int end){
    QSize newsize=itemWidget(projectssubitem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()-list_projects->sizeHintForRow(0));

    if(list_projects->model()!=0){
        if(list_projects->model()->rowCount()==0){
            newsize.setHeight(0);
        }
    }
    projectssubitem->setSizeHint(0,newsize);

    updatelayouttimer->start();
}

void VisionTreeWidget::VisionProjectsrowsAboutToBeInserted(QModelIndex modelindex,int start,int end){

    QSize newsize=itemWidget(projectssubitem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()+list_projects->sizeHintForRow(0));
    projectssubitem->setSizeHint(0,newsize);

}


void VisionTreeWidget::VisionProjectsrowsInserted(QModelIndex modelindex,int start,int end){

    updatelayouttimer->start();
}


void VisionTreeWidget::InspectionsrowsAboutToBeInserted(QModelIndex modelindex,int start,int end){

    QSize newsize=itemWidget(inspectionssubitem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()+list_inspections->sizeHintForRow(0));
    inspectionssubitem->setSizeHint(0,newsize);

}


void VisionTreeWidget::InspectionsrowsInserted(QModelIndex modelindex,int start,int end){

    updatelayouttimer->start();
}


void VisionTreeWidget::bt_projectClicked(){
    projectsitem->setExpanded(!projectsitem->isExpanded());
}


void VisionTreeWidget::bt_InspectionClicked(){
    inspectionsitem->setExpanded(!inspectionsitem->isExpanded());
}

void VisionTreeWidget::AddVisionProjectsModel(ProjectsList *VisionProjects){


    connect(VisionProjects,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this,SLOT(VisionProjectsdataChanged(QModelIndex,QModelIndex)));
    connect(VisionProjects,SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),this,SLOT(VisionProjectsrowsAboutToBeInserted(QModelIndex,int,int)));
    connect(VisionProjects,SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(VisionProjectsrowsInserted(QModelIndex,int,int)));
    connect(VisionProjects,SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),this,SLOT(VisionProjectsrowsAboutToBeRemoved(QModelIndex,int,int)));
    connect(VisionProjects,SIGNAL(rowsRemoved(QModelIndex,int,int)),this,SLOT(VisionProjectsrowsRemoved(QModelIndex,int,int)));







    projectssubitem=new QTreeWidgetItem(0);

    projectsitem->setData(0,Qt::UserRole,1); // parent item

    projectssubitem->setData(0,Qt::UserRole,2); // child

    projectsitem->addChild(projectssubitem);


    projectssubitem->setDisabled(true);


    
    projectsitem->setDisabled(true);

    //Projects
    {
        QFrame *frame=new QFrame(this);
        QVBoxLayout *lay=new QVBoxLayout(frame);
        frame->setFrameShape(Shape::Box);
        frame->setFrameShadow(Shadow::Plain);
        lay->setContentsMargins(1,1,1,1);
        lay->setSpacing(2);
        QPushButton *bt_load=new QPushButton();
        bt_load->sizePolicy().setVerticalPolicy(QSizePolicy::Fixed);
        bt_load->setText(tr("Load"));
        lay->addWidget(bt_load);
        list_projects= new KPPAdjustableListView();
        list_projects->setModel(VisionProjects);
        connect(list_projects,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(SelectionChanged(QItemSelection,QItemSelection)));
        lay->addWidget(list_projects);
        frame->setLayout(lay);

        frame->setAutoFillBackground(true);
        this->setItemWidget(projectssubitem,0,frame);

        QSize newsize=itemWidget(projectssubitem,0)->contentsRect().size();
        newsize.setHeight(newsize.height());
        projectssubitem->setSizeHint(0,newsize);
    }


    inspectionsitem->setData(0,Qt::UserRole,1); // parent item

    inspectionssubitem=new QTreeWidgetItem(0);
    inspectionssubitem->setData(0,Qt::UserRole,2); // child

    inspectionsitem->addChild(inspectionssubitem);

    inspectionsitem->setDisabled(true);

    inspectionssubitem->setDisabled(true);

    //Inspections
    {
        QFrame *frame=new QFrame(this);
        frame->setFrameShape(Shape::Box);
        frame->setFrameShadow(Shadow::Plain);
        frame->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
        QVBoxLayout *lay=new QVBoxLayout(frame);
        lay->setContentsMargins(1,1,1,1);
        lay->setSpacing(2);

        list_inspections= new KPPAdjustableListView();
        //list_projects->setModel(VisionProjects);

        lay->addWidget(list_inspections);
        frame->setLayout(lay);

        frame->setAutoFillBackground(true);
        this->setItemWidget(inspectionssubitem,0,frame);

        QSize newsize=itemWidget(inspectionssubitem,0)->contentsRect().size();

        int list_height=list_inspections->sizeHint().height();
        newsize.setHeight(newsize.height()+list_height);
        inspectionssubitem->setSizeHint(0,newsize);
    }
}

void VisionTreeWidget::SelectionChanged(QItemSelection , QItemSelection){

    if(sender()->objectName()==list_projects->objectName()){
        QModelIndexList selectedlist= list_projects->selectionModel()->selectedRows();
        if(selectedlist.count()>0)
            setSelectedProject(selectedlist.at(0).data(Qt::UserRole).value<KPPVision*>());
        else
            setSelectedProject(0);
    }
    else if(sender()->objectName()==list_inspections->objectName()){
        //        QModelIndexList selectedlist= ui->list_inspections->selectionModel()->selectedRows();

        //        setSelectedInspection(selectedlist.at(0).data(Qt::UserRole).value<Inspection*>());
    }
}


void VisionTreeWidget::setSelectedProject(KPPVision *value)
{

    if(m_selectedProject!=0){
        disconnect(m_selectedProject->inspectionList(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),this,0);
        disconnect(m_selectedProject->inspectionList(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,0);
    }


    if (value!=0) {
        bt_inspect->setEnabled(true);
        list_inspections->setModel(value->inspectionList());



        connect(value->inspectionList(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),this,SLOT(InspectionsrowsAboutToBeInserted(QModelIndex,int,int)),Qt::UniqueConnection);
        connect(value->inspectionList(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(InspectionsrowsInserted(QModelIndex,int,int)),Qt::UniqueConnection);


    }
    else{
        bt_inspect->setEnabled(false);
        inspectionsitem->setExpanded(false);
    }

    m_selectedProject=value;
}
