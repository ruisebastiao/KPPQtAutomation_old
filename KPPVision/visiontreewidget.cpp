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




    Projectsitem=new KPPTreeWidgetItem(0);
    bt_Projects= new QPushButton(this);
    connect(bt_Projects,SIGNAL(clicked()),this,SLOT(bt_projectClicked()));
    bt_Projects->setText(tr("Projects"));
    bt_Projects->setAutoFillBackground(true);
    addTopLevelItem(Projectsitem);
    this->setItemWidget(Projectsitem,0,bt_Projects);



    RequestsItem=new KPPTreeWidgetItem(0);
    bt_Request= new QPushButton(this);
    connect(bt_Request,SIGNAL(clicked()),this,SLOT(bt_RequestClicked()));
    bt_Request->setText(tr("Requests"));
    bt_Request->setEnabled(false);

    addTopLevelItem(RequestsItem);
    bt_Request->setAutoFillBackground(true);
    this->setItemWidget(RequestsItem,0,bt_Request);


    InspectionsItem=new KPPTreeWidgetItem(0);
    bt_Inspections= new QPushButton(this);
    connect(bt_Inspections,SIGNAL(clicked()),this,SLOT(bt_InspectionsClicked()));
    bt_Inspections->setText(tr("Inspections"));
    bt_Inspections->setEnabled(false);

    addTopLevelItem(InspectionsItem);
    bt_Inspections->setAutoFillBackground(true);
    this->setItemWidget(InspectionsItem,0,bt_Inspections);


    m_selectedProject=0;
    m_selectedRequest=0;
    m_selectedInspection=0;



}


void VisionTreeWidget::VisionProjectsDataChanged(QModelIndex start,QModelIndex end){

    list_Projects->repaint();
}

void VisionTreeWidget::VisionProjectsRowsAboutToBeRemoved(QModelIndex modelindex,int start,int end){

}


void VisionTreeWidget::VisionProjectsRowsRemoved(QModelIndex modelindex,int start,int end){
    QSize newsize=itemWidget(ProjectsSubItem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()-list_Projects->sizeHintForRow(0));

    if(list_Projects->model()!=0){
        if(list_Projects->model()->rowCount()==0){
            newsize.setHeight(0);
        }
    }
    ProjectsSubItem->setSizeHint(0,newsize);

    updatelayouttimer->start();
}

void VisionTreeWidget::VisionProjectsRowsAboutToBeInserted(QModelIndex modelindex,int start,int end){

    QSize newsize=itemWidget(ProjectsSubItem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()+list_Projects->sizeHintForRow(0));
    ProjectsSubItem->setSizeHint(0,newsize);

}


void VisionTreeWidget::VisionProjectsRowsInserted(QModelIndex modelindex,int start,int end){

    updatelayouttimer->start();
}


void VisionTreeWidget::RequestsRowsAboutToBeInserted(QModelIndex modelindex,int start,int end){

    QSize newsize=itemWidget(RequestsSubItem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()+list_Requests->sizeHintForRow(0));
    RequestsSubItem->setSizeHint(0,newsize);

}


void VisionTreeWidget::RequestsRowsInserted(QModelIndex modelindex,int start,int end){

    updatelayouttimer->start();
}



void VisionTreeWidget::RequestsRowsRemoved(QModelIndex modelindex,int start,int end){
    QSize newsize=itemWidget(RequestsSubItem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()-list_Requests->sizeHintForRow(0));

    if(list_Requests->model()!=0){
        if(list_Requests->model()->rowCount()==0){
            newsize.setHeight(0);
        }
    }
    RequestsSubItem->setSizeHint(0,newsize);

    updatelayouttimer->start();
}


void VisionTreeWidget::InspectionrowsAboutToBeRemoved(QModelIndex modelindex,int start,int end){

}


void VisionTreeWidget::InspectionsRowsRemoved(QModelIndex modelindex,int start,int end){
    QSize newsize=itemWidget(InspectionsSubItem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()-list_Inspections->sizeHintForRow(0));

    if(list_Inspections->model()!=0){
        if(list_Inspections->model()->rowCount()==0){
            newsize.setHeight(0);
        }
    }
    InspectionsSubItem->setSizeHint(0,newsize);

    updatelayouttimer->start();
}

void VisionTreeWidget::InspectionrowsAboutToBeInserted(QModelIndex modelindex,int start,int end){

    QSize newsize=itemWidget(InspectionsSubItem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()+list_Inspections->sizeHintForRow(0));
    InspectionsSubItem->setSizeHint(0,newsize);

}


void VisionTreeWidget::InspectionrowsRowsInserted(QModelIndex modelindex,int start,int end){

    updatelayouttimer->start();
}

void VisionTreeWidget::bt_projectClicked(){
    Projectsitem->setExpanded(!Projectsitem->isExpanded());
}


void VisionTreeWidget::bt_RequestClicked(){
    RequestsItem->setExpanded(!RequestsItem->isExpanded());
}

void VisionTreeWidget::bt_InspectionsClicked(){
    InspectionsItem->setExpanded(!InspectionsItem->isExpanded());
}

void VisionTreeWidget::AddVisionProjectsModel(KPPVisionList<KPPVision> *VisionProjects){


    connect(VisionProjects,SIGNAL(dataChanged(QModelIndex,QModelIndex))
            ,this,SLOT(VisionProjectsDataChanged(QModelIndex,QModelIndex)));

    connect(VisionProjects,SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),
            this,SLOT(VisionProjectsRowsAboutToBeInserted(QModelIndex,int,int)));

    connect(VisionProjects,SIGNAL(rowsInserted(QModelIndex,int,int)),
            this,SLOT(VisionProjectsRowsInserted(QModelIndex,int,int)));

    connect(VisionProjects,SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
            this,SLOT(VisionProjectsRowsAboutToBeRemoved(QModelIndex,int,int)));

    connect(VisionProjects,SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this,SLOT(VisionProjectsRowsRemoved(QModelIndex,int,int)));



    //Projects
    {
        ProjectsSubItem=new QTreeWidgetItem(0);

        Projectsitem->setData(0,Qt::UserRole,1); // parent item

        ProjectsSubItem->setData(0,Qt::UserRole,2); // child

        Projectsitem->addChild(ProjectsSubItem);


        ProjectsSubItem->setDisabled(true);



        Projectsitem->setDisabled(true);

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
        list_Projects= new KPPAdjustableListView();
        list_Projects->setObjectName("list_projects");
        list_Projects->setModel(VisionProjects);
        connect(list_Projects,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(SelectionChanged(QItemSelection,QItemSelection)));


        lay->addWidget(list_Projects);


       QSpacerItem* verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        lay->addSpacerItem(verticalSpacer);
        frame->setLayout(lay);

        frame->setAutoFillBackground(true);
        this->setItemWidget(ProjectsSubItem,0,frame);

        QSize newsize=itemWidget(ProjectsSubItem,0)->contentsRect().size();
        newsize.setHeight(newsize.height());
        ProjectsSubItem->setSizeHint(0,newsize);

    }

    //Requests
    {
        RequestsItem->setData(0,Qt::UserRole,1); // parent item

        RequestsSubItem=new QTreeWidgetItem(0);
        RequestsSubItem->setData(0,Qt::UserRole,2); // child

        RequestsItem->addChild(RequestsSubItem);

        RequestsItem->setDisabled(true);

        RequestsSubItem->setDisabled(true);

        QFrame *frame=new QFrame(this);
        frame->setFrameShape(Shape::Box);
        frame->setFrameShadow(Shadow::Plain);
        frame->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
        QVBoxLayout *lay=new QVBoxLayout(frame);
        lay->setContentsMargins(1,1,1,1);


        list_Requests= new KPPAdjustableListView();
        list_Requests->setObjectName("list_requests");

        lay->addWidget(list_Requests);
        QSpacerItem* verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

         lay->addSpacerItem(verticalSpacer);

        frame->setLayout(lay);

        frame->setAutoFillBackground(true);
        this->setItemWidget(RequestsSubItem,0,frame);

        QSize newsize=itemWidget(RequestsSubItem,0)->contentsRect().size();

        int list_height=list_Requests->sizeHint().height();
        newsize.setHeight(newsize.height()+list_height);
        RequestsSubItem->setSizeHint(0,newsize);



        connect(list_Requests,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(SelectionChanged(QItemSelection,QItemSelection)));

    }

    // Inspections
    {


        InspectionsItem->setData(0,Qt::UserRole,1); // parent item

        InspectionsSubItem=new QTreeWidgetItem(0);
        InspectionsSubItem->setData(0,Qt::UserRole,2); // child

        InspectionsItem->addChild(InspectionsSubItem);

        InspectionsItem->setDisabled(true);

        InspectionsSubItem->setDisabled(true);

        QFrame *frame=new QFrame(this);
        frame->setFrameShape(Shape::Box);
        frame->setFrameShadow(Shadow::Plain);
        frame->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
        QVBoxLayout *lay=new QVBoxLayout(frame);
        lay->setContentsMargins(1,1,1,1);


        list_Inspections= new KPPAdjustableListView();
        list_Inspections->setObjectName("list_Inspections");

        lay->addWidget(list_Inspections);
        QSpacerItem* verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

         lay->addSpacerItem(verticalSpacer);
        frame->setLayout(lay);

        frame->setAutoFillBackground(true);
        this->setItemWidget(InspectionsSubItem,0,frame);

        QSize newsize=itemWidget(InspectionsSubItem,0)->contentsRect().size();

        int list_height=list_Inspections->sizeHint().height();
        newsize.setHeight(newsize.height()+list_height);
        InspectionsSubItem->setSizeHint(0,newsize);


        connect(list_Inspections,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(SelectionChanged(QItemSelection,QItemSelection)));



    }


}

void VisionTreeWidget::SelectionChanged(QItemSelection , QItemSelection){

    if(sender()->objectName()==list_Projects->objectName()){
        QModelIndexList selectedlist= list_Projects->selectionModel()->selectedRows();
        if(selectedlist.count()>0)
            setSelectedProject(selectedlist.at(0).data(Qt::UserRole).value<KPPVision*>());
        else
            setSelectedProject(0);


    }
    else if(sender()->objectName()==list_Requests->objectName()){
        QModelIndexList selectedlist= list_Requests->selectionModel()->selectedRows();
        if(selectedlist.count()>0)
            setSelectedRequest(selectedlist.at(0).data(Qt::UserRole).value<Request*>());
        else
            setSelectedRequest(0);


    }
    else if(sender()->objectName()==list_Inspections->objectName()){
        QModelIndexList selectedlist= list_Inspections->selectionModel()->selectedRows();
        if(selectedlist.count()>0)
            setSelectedInspection(selectedlist.at(0).data(Qt::UserRole).value<Inspection*>());
        else
            setSelectedInspection(0);


    }

}


void VisionTreeWidget::setSelectedProject(KPPVision *value)
{

    if(m_selectedProject!=0){
        disconnect(m_selectedProject->Requests(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),this,0);
        disconnect(m_selectedProject->Requests(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,0);
        disconnect(m_selectedProject->Requests(),SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this,0);
    }


    if (value!=0) {
        bt_Request->setEnabled(true);
        list_Requests->setModel(value->Requests());

        connect(value->Requests(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),
                this,SLOT(RequestsRowsAboutToBeInserted(QModelIndex,int,int)),Qt::UniqueConnection);
        connect(value->Requests(),SIGNAL(rowsInserted(QModelIndex,int,int)),
                this,SLOT(RequestsRowsInserted(QModelIndex,int,int)),Qt::UniqueConnection);
        connect(value->Requests(),SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this,SLOT(RequestsRowsRemoved(QModelIndex,int,int)));


    }
    else{
        bt_Request->setEnabled(false);
        RequestsItem->setExpanded(false);
    }

    m_selectedProject=value;

    QSize newsize=itemWidget(RequestsSubItem,0)->contentsRect().size();
    newsize.setHeight(list_Requests->sizeHint().height());
    RequestsSubItem->setSizeHint(0,newsize);
    updatelayouttimer->start();

    emit ListSelectionChanged(m_selectedProject);
}

void VisionTreeWidget::setSelectedRequest(Request *value)
{



    if(m_selectedRequest!=0){
        disconnect(m_selectedRequest->Inspections(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),
                   this,0);
        disconnect(m_selectedRequest->Inspections(),SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this,0);

        disconnect(m_selectedRequest->Inspections(),SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this,0);
    }


    if (value!=0) {
        bt_Inspections->setEnabled(true);
        list_Inspections->setModel(value->Inspections());

        connect(value->Inspections(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),
                this,SLOT(InspectionrowsAboutToBeInserted(QModelIndex,int,int)),Qt::UniqueConnection);
        connect(value->Inspections(),SIGNAL(rowsInserted(QModelIndex,int,int)),
                this,SLOT(InspectionrowsRowsInserted(QModelIndex,int,int)),Qt::UniqueConnection);
        connect(value->Inspections(),SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this,SLOT(InspectionsRowsRemoved(QModelIndex,int,int)));

    }
    else{
        bt_Inspections->setEnabled(false);
        InspectionsItem->setExpanded(false);
    }

    m_selectedRequest=value;

    QSize newsize=itemWidget(InspectionsSubItem,0)->contentsRect().size();
    newsize.setHeight(list_Inspections->sizeHint().height());
    InspectionsSubItem->setSizeHint(0,newsize);

    updatelayouttimer->start();

    emit ListSelectionChanged(m_selectedRequest);
}

void VisionTreeWidget::setSelectedInspection(Inspection *value)
{


        if(m_selectedInspection!=0){
//            disconnect(m_selectedInspection->Requests(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),this,0);
//            disconnect(m_selectedInspection->Requests(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,0);
        }


        if (value!=0) {
//            bt_request->setEnabled(true);
//            list_requests->setModel(value->Requests());

//            connect(value->Requests(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),this,SLOT(RequestsrowsAboutToBeInserted(QModelIndex,int,int)),Qt::UniqueConnection);
//            connect(value->Requests(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(RequestsrowsInserted(QModelIndex,int,int)),Qt::UniqueConnection);


        }
        else{
//            bt_request->setEnabled(false);
//            RequestsItem->setExpanded(false);
        }

       m_selectedInspection=value;

        QSize newsize=itemWidget(InspectionsSubItem,0)->contentsRect().size();
        newsize.setHeight(list_Inspections->sizeHint().height());
        InspectionsSubItem->setSizeHint(0,newsize);

        updatelayouttimer->start();

        emit ListSelectionChanged(m_selectedInspection);
}