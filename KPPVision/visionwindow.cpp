#include "visionwindow.h"
#include "ui_visionwindow.h"

VisionWindow::VisionWindow(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::VisionWindow)
{
    ui->setupUi(this);

    new Settings(this);
    if(!(Settings::AppSettings->Load(qApp->applicationDirPath().append("/settings.cfg")))){
        Settings::AppSettings->Save();
    }

    if(!Settings::AppSettings->Projects()->Load(Settings::AppSettings->ProjectsFilePath())){
        Settings::AppSettings->Projects()->Save();
    }

    ui->treeWidget->AddVisionProjectsModel(Settings::AppSettings->Projects());

    //Settings::AppSettings->Projects()->AddItem("asd");


    configs= new ConfigurationsWidget (this);



    connect(ui->treeWidget,SIGNAL(ListSelectionChanged(QObject*)),this,SLOT(VisionTreeListSelectionChanged(QObject*)));

    Settings::mainwidget=this;


    foreach (KPPVision *project, Settings::AppSettings->Projects()->getList()) {
        foreach (Request *request, project->Requests()->getList()) {
            connect(request->Inspections(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(InspectionInserted(QModelIndex,int,int)));
            foreach (Inspection *inspection, request->Inspections()->getList()) {
                inspection->setView(ui->graphicsView);
            }

        }
    }


//    for(KPPVision *project : Settings::AppSettings->Projects()->getList()) {
//        for(Request *request: project->Requests()->getList()) {
//            connect(request->Inspections(),SIGNAL(rowsInserted(QModelIndex,int,int)),this,SLOT(InspectionInserted(QModelIndex,int,int)));
//            for(Inspection *inspection: request->Inspections()->getList()) {

//                inspection->setView(ui->graphicsView);

//            }

//        }

//    }

    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
    QIcon icon;
    icon.addFile(QStringLiteral(":/icons/next"), QSize(), QIcon::Normal, QIcon::Off);
    icon.addFile(QStringLiteral(":/icons/prev"), QSize(), QIcon::Active, QIcon::On);
    ui->bt_toogleSideMenu->setIcon(icon);
}

VisionWindow::~VisionWindow()
{
    delete ui;
}

void VisionWindow::toogleModuleSettings()
{
 configs->ToogleState();
}



void VisionWindow::VisionTreeListSelectionChanged(QObject* newselection){
    if (dynamic_cast<KPPVision*>(newselection)) {

        configs->setSelectedProject(dynamic_cast<KPPVision*>(newselection));
    }
    else if (dynamic_cast<Request*>(newselection)) {
        configs->setSelectedRequest(dynamic_cast<Request*>(newselection));
    }
    else if (dynamic_cast<Inspection*>(newselection)) {
        configs->setSelectedInspection(dynamic_cast<Inspection*>(newselection));
    }
}

void VisionWindow::InspectionInserted(QModelIndex index, int start, int end)
{


    Inspection* insp=index.data(Qt::UserRole).value<Inspection*>();
    if(insp!=0)
        insp->setView(ui->graphicsView);
}

void VisionWindow::on_bt_toogleSideMenu_clicked(bool checked)
{
    if(checked){

        ui->sideWidget->setMenuState(SideWidget::Opened);

    }
    else{
        ui->sideWidget->setMenuState(SideWidget::Closed);
    }
}
