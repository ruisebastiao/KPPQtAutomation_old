#include "visiontreewidget.h"
#include "QBoxLayout"
#include "QDebug"
#include "kppvision.h"
#include "settings.h"
#include "kppadjustablelistview.h"
#include "kppanimatedframe.h"
#include "qapplication.h"
#include "qmainwindow.h"



using namespace Vision;


VisionTreeWidget::VisionTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    setRootIsDecorated(false);
    setHeaderHidden(true);
    setIndentation(0);
    setAnimated(true);
    parentWidget=parent;
    // setAutoExpandDelay();

    updatelayouttimer= new QTimer(this);
    updatelayouttimer->setSingleShot(true);
    updatelayouttimer->setInterval(150);
    connect(updatelayouttimer, SIGNAL(timeout()), this, SLOT(doItemsLayout()));




    Projectsitem=new KPPTreeWidgetItem(0);
    bt_Projects= new KPPRootTreePushButton("Projects",Projectsitem);
    // connect(bt_Projects,SIGNAL(clicked()),this,SLOT(bt_projectClicked()));
    bt_Projects->setText(tr("Projects"));
    bt_Projects->setAutoFillBackground(true);
    addTopLevelItem(Projectsitem);
    this->setItemWidget(Projectsitem,0,bt_Projects);



    RequestsItem=new KPPTreeWidgetItem(0);
    bt_Request= new KPPRootTreePushButton("Requests",RequestsItem);

    //bt_Request->setEnabled(false);

    addTopLevelItem(RequestsItem);
    bt_Request->setAutoFillBackground(true);
    this->setItemWidget(RequestsItem,0,bt_Request);


    InspectionsItem=new KPPTreeWidgetItem(0);
    bt_Inspections= new KPPRootTreePushButton("Inspections",InspectionsItem);

    // bt_Inspections->setEnabled(false);

    addTopLevelItem(InspectionsItem);
    bt_Inspections->setAutoFillBackground(true);
    this->setItemWidget(InspectionsItem,0,bt_Inspections);

    ROIItem=new KPPTreeWidgetItem(0);
    bt_ROI= new KPPRootTreePushButton("ROIS",ROIItem);

    //bt_ROI->setEnabled(false);

    addTopLevelItem(ROIItem);
    bt_ROI->setAutoFillBackground(true);
    this->setItemWidget(ROIItem,0,bt_ROI);


    m_SelectedProject=0;





    m_requestmenu=new RequestMenu(parent);
    m_inspectionmenu=new InspectionMenu(parent);

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

void VisionTreeWidget::ListItemPressed(QModelIndex e)
{



    if(sender()->objectName()==list_Requests->objectName()){
        QRect wt=list_Requests->visualRect(e);
        QRect mappedrect=QRect(list_Requests->mapTo(parentWidget,wt.topLeft()),list_Requests->mapTo(Settings::mainwidget,wt.bottomRight()));
        m_requestmenu->setAlignmentRect(mappedrect);
    }
    else if(sender()->objectName()==list_Inspections->objectName()){
        QRect wt=list_Inspections->visualRect(e);
        QRect mappedrect=QRect(list_Inspections->mapTo(parentWidget,wt.topLeft()),list_Inspections->mapTo(Settings::mainwidget,wt.bottomRight()));
        m_inspectionmenu->setAlignmentRect(mappedrect);
    }


    //  }
}

void VisionTreeWidget::ListItemSwipeRight()
{
    if(sender()->objectName()==list_Requests->objectName()){

        m_requestmenu->setSelectedRequest(m_SelectedProject->SelectedRequest());
        m_requestmenu->show();

    }
    else  if(sender()->objectName()==list_Inspections->objectName()){


        m_inspectionmenu->show();

    }
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

void VisionTreeWidget::ROIrowsAboutToBeInserted(QModelIndex modelindex,int start,int end){

    QSize newsize=itemWidget(ROISubItem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()+list_ROIS->sizeHintForRow(0));
    ROISubItem->setSizeHint(0,newsize);

}
void VisionTreeWidget::ROIRowsInserted(QModelIndex modelindex,int start,int end){

    updatelayouttimer->start();
}



void VisionTreeWidget::ROIRowsRemoved(QModelIndex modelindex,int start,int end){
    QSize newsize=itemWidget(ROISubItem,0)->contentsRect().size();
    newsize.setHeight(newsize.height()-list_ROIS->sizeHintForRow(0));

    if(list_ROIS->model()!=0){
        if(list_ROIS->model()->rowCount()==0){
            newsize.setHeight(0);
        }
    }
    ROISubItem->setSizeHint(0,newsize);

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

void VisionTreeWidget::bt_ROIClicked(){
    ROIItem->setExpanded(!ROIItem->isExpanded());
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
        lay->setContentsMargins(4,4,4,4);
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

        list_Requests->setGrabEnable(true);

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
        connect(list_Requests,SIGNAL(pressed(QModelIndex)),this,SLOT(ListItemPressed(QModelIndex)));
        connect(list_Requests,SIGNAL(SwipedRight()),this,SLOT(ListItemSwipeRight()));

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

        list_Inspections->setGrabEnable(true);

        connect(list_Inspections,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(SelectionChanged(QItemSelection,QItemSelection)));
        connect(list_Inspections,SIGNAL(pressed(QModelIndex)),this,SLOT(ListItemPressed(QModelIndex)));
        connect(list_Inspections,SIGNAL(SwipedRight()),this,SLOT(ListItemSwipeRight()));




    }

    // ROIS
    {


        ROIItem->setData(0,Qt::UserRole,1); // parent item

        ROISubItem=new QTreeWidgetItem(0);
        ROISubItem->setData(0,Qt::UserRole,2); // child

        ROIItem->addChild(ROISubItem);

        ROIItem->setDisabled(true);

        ROISubItem->setDisabled(true);

        QFrame *frame=new QFrame(this);
        frame->setFrameShape(Shape::Box);
        frame->setFrameShadow(Shadow::Plain);
        frame->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
        QVBoxLayout *lay=new QVBoxLayout(frame);
        lay->setContentsMargins(1,1,1,1);


        list_ROIS= new KPPAdjustableListView();
        list_ROIS->setObjectName("list_ROIS");

        lay->addWidget(list_ROIS);
        QSpacerItem* verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::Expanding);

        lay->addSpacerItem(verticalSpacer);
        frame->setLayout(lay);

        frame->setAutoFillBackground(true);
        this->setItemWidget(ROISubItem,0,frame);

        QSize newsize=itemWidget(ROISubItem,0)->contentsRect().size();

        int list_height=list_ROIS->sizeHint().height();
        newsize.setHeight(newsize.height()+list_height);
        ROISubItem->setSizeHint(0,newsize);

        list_ROIS->setGrabEnable(true);

        connect(list_ROIS,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(SelectionChanged(QItemSelection,QItemSelection)));
        connect(list_ROIS,SIGNAL(pressed(QModelIndex)),this,SLOT(ListItemPressed(QModelIndex)));
        connect(list_ROIS,SIGNAL(SwipedRight()),this,SLOT(ListItemSwipeRight()));




    }


}

/*
 *
    QWidget* t=Settings::mainwidget;
    KPPAnimatedFrame* teste=new KPPAnimatedFrame(t,Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint,bt_Request);
    teste->show();
*/

void VisionTreeWidget:: SelectionChanged(QItemSelection , QItemSelection){

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
    else if(sender()->objectName()==list_ROIS->objectName()){
        QModelIndexList selectedroi= list_ROIS->selectionModel()->selectedRows();
        if(selectedroi.count()>0)
            setSelectedROI(selectedroi.at(0).data(Qt::UserRole).value<ROI*>());
        else
            setSelectedROI(0);


    }

}


void VisionTreeWidget::setSelectedProject(KPPVision *value)
{

    if(m_SelectedProject!=0){
        disconnect(m_SelectedProject->Requests(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),this,0);
        disconnect(m_SelectedProject->Requests(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,0);
        disconnect(m_SelectedProject->Requests(),SIGNAL(rowsRemoved(QModelIndex,int,int)),
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

    m_SelectedProject=value;

    QSize newsize=itemWidget(RequestsSubItem,0)->contentsRect().size();
    newsize.setHeight(list_Requests->sizeHint().height());
    RequestsSubItem->setSizeHint(0,newsize);
    updatelayouttimer->start();

    emit ListSelectionChanged(m_SelectedProject);
}

void VisionTreeWidget::setSelectedRequest(Request *value)
{



    if(m_SelectedProject->SelectedRequest()!=0){
        disconnect(m_SelectedProject->SelectedRequest()->Inspections(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),
                   this,0);
        disconnect(m_SelectedProject->SelectedRequest()->Inspections(),SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this,0);

        disconnect(m_SelectedProject->SelectedRequest()->Inspections(),SIGNAL(rowsRemoved(QModelIndex,int,int)),
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

    m_SelectedProject->setSelectedRequest(value);

    QSize newsize=itemWidget(InspectionsSubItem,0)->contentsRect().size();
    newsize.setHeight(list_Inspections->sizeHint().height());
    InspectionsSubItem->setSizeHint(0,newsize);

    updatelayouttimer->start();

    emit ListSelectionChanged(m_SelectedProject->SelectedRequest());
}

void VisionTreeWidget::setSelectedInspection(Inspection *value)
{

      m_inspectionmenu->setSelectedInspection(value);
    if(m_SelectedProject->SelectedRequest()->SelectedInspection()!=0){
        disconnect(m_SelectedProject->SelectedRequest()->SelectedInspection()->ROIs(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),
                   this,0);
        disconnect(m_SelectedProject->SelectedRequest()->SelectedInspection()->ROIs(),SIGNAL(rowsInserted(QModelIndex,int,int)),
                   this,0);

        disconnect(m_SelectedProject->SelectedRequest()->SelectedInspection()->ROIs(),SIGNAL(rowsRemoved(QModelIndex,int,int)),
                   this,0);

        disconnect(m_SelectedProject->SelectedRequest()->SelectedInspection()->InspectionScene(),SIGNAL(selectionChanged()),
                   this,0);
    }


    if (value!=0) {
        bt_ROI->setEnabled(true);
        list_ROIS->setModel(value->ROIs());

        connect(value->ROIs(),SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),
                this,SLOT(ROIrowsAboutToBeInserted(QModelIndex,int,int)),Qt::UniqueConnection);
        connect(value->ROIs(),SIGNAL(rowsInserted(QModelIndex,int,int)),
                this,SLOT(ROIRowsInserted(QModelIndex,int,int)),Qt::UniqueConnection);
        connect(value->ROIs(),SIGNAL(rowsRemoved(QModelIndex,int,int)),
                this,SLOT(ROIRowsRemoved(QModelIndex,int,int)));

        connect(value->InspectionScene(),SIGNAL(selectionChanged()),
                this,SLOT(SceneSelectionChanged()));

    }
    else{
        bt_ROI->setEnabled(false);
        ROIItem->setExpanded(false);
    }

    m_SelectedProject->SelectedRequest()->setSelectedInspection(value);

    if(m_SelectedProject->SelectedRequest()->SelectedInspection()!=0){

        m_SelectedProject->SelectedRequest()->SelectedInspection()->UpdateScene();

    }

    QSize newsize=itemWidget(InspectionsSubItem,0)->contentsRect().size();
    newsize.setHeight(list_Inspections->sizeHint().height());
    InspectionsSubItem->setSizeHint(0,newsize);

    updatelayouttimer->start();

    emit ListSelectionChanged(m_SelectedProject->SelectedRequest()->SelectedInspection());
}

void VisionTreeWidget::SceneSelectionChanged(){
    ROI* selectedROI=0;
    if(m_SelectedProject->SelectedRequest()->SelectedInspection()->InspectionScene()->selectedItems().count()==1){
        selectedROI=dynamic_cast<ROI*>(m_SelectedProject->SelectedRequest()->SelectedInspection()->InspectionScene()->selectedItems().at(0));
       // setSelectedROI(selectedROI);


        QVariant item;
        item.setValue<ROI*>(selectedROI);
        QModelIndexList list= list_ROIS->model()->match(list_ROIS->model()->index(0,0),Qt::UserRole,item,-1,Qt::MatchExactly);
        if(list.count()>0)
            list_ROIS->setCurrentIndex(list.at(0));
        else
            list_ROIS-> selectionModel()->clearSelection();
    }
    else
        list_ROIS->selectionModel()->clearSelection();

    //setSelectedROI(0);
}

void VisionTreeWidget::setSelectedROI(ROI *value)
{
    if(value==m_SelectedProject->SelectedRequest()->SelectedInspection()->SelectedROI())
        return;


    if(m_SelectedProject->SelectedRequest()->SelectedInspection()->SelectedROI()!=0){
        m_SelectedProject->SelectedRequest()->SelectedInspection()->SelectedROI()->setSelected(false);
    }
    m_SelectedProject->SelectedRequest()->SelectedInspection()->setSelectedROI(value);

    if(value!=0){


        m_SelectedProject->SelectedRequest()->SelectedInspection()->SelectedROI()->setSelected(true);

        QSize newsize=itemWidget(ROISubItem,0)->contentsRect().size();
        newsize.setHeight(list_ROIS->sizeHint().height());
        ROISubItem->setSizeHint(0,newsize);

    }

    updatelayouttimer->start();

    emit ListSelectionChanged(m_SelectedProject->SelectedRequest()->SelectedInspection()->SelectedROI());
}


//void VisionTreeWidget::ROIPressedSlot(ROI *roi)
//{
//            QVariant item;
//            item.setValue<ROI*>(roi);
//            QModelIndexList list= list_ROIS->model()->match(list_ROIS->model()->index(0,0),Qt::UserRole,item);
//            if(list.count()>0)
//                list_ROIS->selectionModel()->select(list.at(0),QItemSelectionModel::ClearAndSelect);
//}
