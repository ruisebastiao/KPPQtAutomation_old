#include "configurationswidget.h"
#include "ui_configurationswidget.h"
#include <QFileDialog>
#include "idseventsthandler.h"
#include "qexception.h"
#include "kppvisionlist.cpp"

using namespace Vision;
using namespace IDS;



ConfigurationsWidget::ConfigurationsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigurationsWidget)
{


    //    QGestureRecognizer* pRecognizer = new SwipeGestureRecognizer();
    //    grabGesture(QGestureRecognizer::registerRecognizer(pRecognizer));
    selectedcam=0;
    m_state=Hiden;
    ui->setupUi(this);

    // setStyleSheet(parentWidget()->styleSheet());
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowTitleHint) ;
    this->setWindowOpacity(0);
    setWindowModality(Qt::WindowModal);
    setWindowTitle(tr("Configurations"));
    animate = new QPropertyAnimation(this, "windowOpacity", this);

    connect(animate,SIGNAL(finished()),this,SLOT(animationFinished()));

    hide();


    ui->edit_projsloc->setText(Settings::AppSettings->ProjectsFilePath());
    ui->list_projects->connect(ui->list_projects,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(selectionChanged(QItemSelection,QItemSelection)));
    ui->list_projects->setModel(Settings::AppSettings->Projects());
    ui->mainpage->setDisplayed(true);
    ui->HardwarePage->setDisplayed(true);

    ui->stackedWidget->setCurrentIndex(1);


    IDSCameraInfo *idscamera=Settings::AppSettings->Hardware()->idsCameraInfo();


    connect(ui->combo_idscameras,SIGNAL(currentIndexChanged(int)),this,SLOT(CurrentIndexChanged(int)));

    ui->combo_idscameras->setModel(idscamera);

    ui->frame_ids_more->SetMaxval(300);
    scene= new QGraphicsScene(this);
    m_PixmapItem = scene->addPixmap(QPixmap());
    ui->graphicsView->setScene(scene);

    ui->bt_snap->hide();
    ui->bt_cont_capture->hide();

    ui->bt_initializecam->setChecked(false);
    ui->check_morecameraoptions->setVisible(false);

    ui->list_req->connect(ui->list_req,SIGNAL(selectionChangedSignal(QItemSelection,QItemSelection)),this,SLOT(selectionChanged(QItemSelection,QItemSelection)));
    ui->bt_removereq->setVisible(false);





}


void ConfigurationsWidget::paintEvent(QPaintEvent *){
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void ConfigurationsWidget::animationFinished(){
    if(m_state==Hiden){
        hide();
    }

}

void ConfigurationsWidget::mousePressEvent(QMouseEvent *event)
{
    offset = event->pos();
    QWidget::mousePressEvent(event);
}
void ConfigurationsWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::RightButton)
    {
        this->move(mapToParent(event->pos() - offset));
    }
    QWidget::mouseMoveEvent(event);

}

ConfigurationsWidget::State ConfigurationsWidget::ToogleState(){

    if(m_state==Visible){
        setState(Hiden);
    }
    else {
        setState(Visible);
    }

    return m_state;

}

ConfigurationsWidget::State ConfigurationsWidget::state() const
{
    return m_state;
}

void ConfigurationsWidget::setState(const State &state)
{

    m_state = state;

    int startval;
    int endval;
    animate->setDuration(150);

    switch (state) {
    case Visible:
        show();
        startval=0;
        endval=1;
        break;
    case Hiden:
        startval=1;
        endval=0;
    default:
        break;
    }

    animate->setStartValue(startval);
    animate->setEndValue(endval);


    animate->start();


}


ConfigurationsWidget::~ConfigurationsWidget()
{
    delete ui;
}

void ConfigurationsWidget::on_bt_exit_clicked()
{
    setState(Hiden);
}


void ConfigurationsWidget::on_bt_select_clicked()
{
    QFileDialog *d=new QFileDialog(this,Qt::Dialog);
    // d->setLocale(QLocale(QLocale::Portuguese, QLocale::Portugal));
    //d->createWindowContainer()
    //LookIn, FileName, FileType, Accept, Reject
    d->setLabelText( QFileDialog::Reject, tr("Cancel"));
    d->setLabelText( QFileDialog::LookIn, tr("Look In"));
    d->setFileMode(QFileDialog::AnyFile);
    d->setDefaultSuffix("qprj");
    d->setNameFilter(tr("Projects file (*.qprj)"));
    if(d->exec()){
        ui->edit_projsloc->setText(d->selectedFiles().at(0));
    }
}

void ConfigurationsWidget::on_bt_save_settings_clicked()
{
    Settings::AppSettings->setProjectsFilePath(ui->edit_projsloc->text());

    Settings::AppSettings->Save();

    Settings::AppSettings->Projects()->Save();


}




void ConfigurationsWidget::on_bt_addproj_clicked()
{
    QString projectname=tr("Projecto 1");
    for (int var = 0; var < Settings::AppSettings->Projects()->rowCount(QModelIndex()); var++) {
        QString newprojname=tr("Projecto ").append("%1").arg(var+2);

        if(!Settings::AppSettings->Projects()->getItemsNameList().contains(newprojname)){
            projectname=newprojname;
            break;
        }
    }
    Settings::AppSettings->Projects()->AddItem(projectname);
}

void ConfigurationsWidget::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{

    if(sender()->objectName()==ui->list_projects->objectName()){
        QModelIndexList selectedlist= ui->list_projects->selectionModel()->selectedRows();
        QString projectname="";
        if (selectedlist.count()>0) {
            projectname=selectedlist.at(0).data().toString();
            setSelectedProject(Settings::AppSettings->Projects()->getItemByName(projectname));
        }
        else
            setSelectedProject(0);


    }
    else if(sender()->objectName()==ui->list_req->objectName()){
        QModelIndexList selectedlist= ui->list_req->selectionModel()->selectedRows();

        if (selectedlist.count()>0) {
            setSelectedRequest(selectedlist.at(0).data(Qt::UserRole).value<Request*>());
        }
        else{
            setSelectedRequest(0);
        }


    }


}



void ConfigurationsWidget::showEvent(QShowEvent *e)
{
    ui->bt_removeproj->setVisible(ui->list_projects->selectionModel()->selectedRows().count()>0);
    QWidget::showEvent(e);
}


void ConfigurationsWidget::on_bt_removeproj_clicked()
{
    QModelIndexList selectedlist= ui->list_projects->selectionModel()->selectedRows();
    KPPVision* project=selectedlist.at(0).data(Qt::UserRole).value<KPPVision*>();

    Settings::AppSettings->Projects()->removeItem(project);
}
KPPVision *ConfigurationsWidget::getSelectedProject() const
{
    return selectedProject;
}

void ConfigurationsWidget::setSelectedProject(KPPVision *value)
{
    selectedProject = value;



    if (selectedProject!=0) {

        ui->inspectionspage->setDisplayed(true);
        ui->bt_removeproj->setVisible(true);


        ui->lbl_projname->setText(selectedProject->getName());
        ui->list_req->setModel(selectedProject->Requests());

        ui->bt_removereq->setVisible(false);
    }
    else{
        ui->inspectionspage->setDisplayed(false);
        if(ui->bt_removeproj->isVisible())
        {
            ui->bt_removeproj->setVisible(false);
        }
        ui->lbl_projname->setText(tr("No Project Selected"));

        ui->list_req->setModel(0);
    }
}

Request *ConfigurationsWidget::SelectedRequest() const
{
    return m_SelectedRequest;
}

void ConfigurationsWidget::setSelectedRequest(Request* SelectedRequest)
{
    m_SelectedRequest= SelectedRequest;
    if(m_SelectedRequest!=0){
        ui->bt_removereq->setVisible(true);
    }
    else{
        ui->bt_removereq->setVisible(false);
    }
}





void ConfigurationsWidget::on_bt_snap_clicked()
{
    selectedcam->setRunMode(IDSCamera::Snap);
    if(selectedcam!=0){
        if(selectedcam->State()==IDSCamera::Started){
            selectedcam->GetImage();
            //QImage captured=selectedcam->GetImage();
            //m_PixmapItem->setPixmap(QPixmap::fromImage(captured));

        }
    }
}

void ConfigurationsWidget::CurrentIndexChanged(int currentIndex)
{
    if(currentIndex>=0){
        QVariant selecteddata= ui->combo_idscameras->currentData();

        selectedcam=selecteddata.value<IDSCamera*>();



        if(selectedcam!=0){

            ui->check_morecameraoptions->setVisible(true);
            connect(selectedcam,SIGNAL(CameraStateChaged(IDSCamera::CameraState)),this,SLOT(IDSCameraStateChanged(IDSCamera::CameraState)),Qt::UniqueConnection);
            connect(selectedcam,SIGNAL(CameraRunModeChaged(IDSCamera::CameraRunMode)),this,SLOT(IDSCameraRunModeChaged(IDSCamera::CameraRunMode)),Qt::UniqueConnection);
            connect(selectedcam,SIGNAL(ImageAvaibleSignal(QPixmap)),this,SLOT(NewImageSlot(QPixmap)),Qt::QueuedConnection);

            if(selectedcam->State()==IDSCamera::Stopped){
                //selectedcam->setInited(true);

                ui->bt_initializecam->setChecked(false);

            }
            else{

                ui->bt_initializecam->setChecked(true);
            }

            bool checked=ui->bt_initializecam->isChecked();
            if(checked){
                checked=false;
            }
        }
        else{
            ui->check_morecameraoptions->setVisible(false);
        }
    }
}


void ConfigurationsWidget::IDSCameraStateChanged(IDSCamera::CameraState NewState)
{
    try
    {
        ui->bt_initializecam->setEnabled(true);
        if(NewState==IDSCamera::Started){
            ui->bt_initializecam->setText(tr("Stop Camera"));
            ui->bt_initializecam->setChecked(true);
            ui->bt_snap->show();
            ui->bt_cont_capture->show();
            m_PixmapItem->setPixmap(QPixmap(selectedcam->ImageWidth(),selectedcam->ImageHeigth()));
            ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
            // teste->getUi()->comboBox->setModel(selectedcam->ImageAOIs());
            //teste->show();
        }
        else{
            ui->bt_initializecam->setText(tr("Start Camera"));
            m_PixmapItem->setPixmap(QPixmap());
            ui->bt_initializecam->setChecked(false);
            ui->bt_snap->hide();
            ui->bt_cont_capture->hide();

        }
    } catch (...) {
        qDebug()<<"Except:";
    }
}

void ConfigurationsWidget::IDSCameraRunModeChaged(IDSCamera::CameraRunMode RunMode)
{
    ui->bt_cont_capture->setEnabled(true);
    if(RunMode==IDSCamera::Continuous){
        ui->bt_cont_capture->setText(tr("Stop Continuous  Capture"));
        ui->bt_cont_capture->setChecked(true);
        ui->bt_snap->hide();

    }
    else{

        ui->bt_cont_capture->setText(tr("Start Continuous  Capture"));
        ui->bt_cont_capture->setChecked(false);
        ui->bt_snap->show();

    }
}

void ConfigurationsWidget::NewImageSlot(QPixmap newpixmap)
{

    m_PixmapItem->setPixmap(newpixmap);
    //m_PixmapItem->set->setPixmap(QPixmap::fromImage(captured));

}

void ConfigurationsWidget::on_bt_cont_capture_clicked()
{
    ui->bt_cont_capture->setEnabled(false);
    if(ui->bt_cont_capture->isChecked()){

        selectedcam->setRunMode(IDSCamera::Continuous);
    }
    else {
        selectedcam->setRunMode(IDSCamera::Snap);
    }
}

void ConfigurationsWidget::on_bt_idscameras_refresh_clicked()
{

}

void ConfigurationsWidget::on_bt_initializecam_clicked()
{

    if(ui->bt_initializecam->isChecked()==true){
        ui->bt_initializecam->setText(tr("Initializing camera..."));
        ui->bt_initializecam->setEnabled(false);
        QApplication::processEvents();
        selectedcam->setState(IDSCamera::Started);
    }
    else{
        ui->bt_initializecam->setText(tr("Stopping camera..."));
        ui->bt_initializecam->setEnabled(false);
        QApplication::processEvents();
        selectedcam->setState(IDSCamera::Stopped);
    }


}



void ConfigurationsWidget::on_check_morecameraoptions_stateChanged(int arg1)
{
    if(arg1){
        ui->frame_ids_more->setFrameVisible(true);
    }
    else{
        ui->frame_ids_more->setFrameVisible(false);
    }
}


void ConfigurationsWidget::on_bt_addreq_clicked()
{

    QString requestname=tr("Request 1");
    for (int var = 0; var < selectedProject->Requests()->rowCount(QModelIndex()); var++) {
        QString request_name=tr("Request ").append("%1").arg(var+2);

        if(!selectedProject->Requests()->getItemsNameList().contains(request_name)){
            requestname=request_name;
            break;
        }
    }


    selectedProject->Requests()->AddItem(requestname);
}

void ConfigurationsWidget::on_bt_removereq_clicked()
{
    QModelIndexList selectedlist= ui->list_req->selectionModel()->selectedRows();

    if(selectedlist.count()>0){

        Request* req=selectedlist.at(0).data(Qt::UserRole).value<Request*>();

        selectedProject->Requests()->removeItem(req);


    }
}
