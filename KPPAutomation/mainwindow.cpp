#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "actionbar.h"
#include "qlineedit.h"
#include "settings.h"
#include "crashdialog.h"
#include "kppvisionlist.h"
#include "type_traits"
#include "QDesktopWidget"

using namespace Vision;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Serializer serializer;
    ui->setupUi(this);

    Settings::AppSettings= new Settings(this);

    Settings::AppSettings->Load(qApp->applicationDirPath()+"/settings.cfg");

    ui->actionlayout->setMargin(0);
    ui->actionlayout->setSizeConstraint(QLayout::SetNoConstraint);

    ActionBar* actionBar=new ActionBar(ui->mainWidget);
    //actionBar->setTitle(tr("News"),true);
    //actionBar->addAction(new QAction(tr("Weather"),this));
    //actionBar->addAction(new QAction(tr("Sports"),this));




    actionBar->addButton(new QAction(QIcon(":/icons/settings"),tr("Configurations"),this));
    actionBar->addButton(new QAction(QIcon(":/icons/cancel"),tr("Exit"),this));
    //    actionBar->addButton(new QAction(QIcon(":/icons/chat"),tr("Chat"),this));
    //    actionBar->addButton(new QAction(QIcon(":/icons/email"),tr("Email"),this));
    //    actionBar->addButton(new QAction(QIcon(":/icons/bad"),tr("Bad"),this));
    //    actionBar->addButton(new QAction(QIcon(":/icons/good"),tr("Good"),this));

    connect(actionBar,SIGNAL(up()),SLOT(bt_Cliked()));
    connect(actionBar,SIGNAL(ActionButtonClicked(QToolButton*)),SLOT(ActionButtonClicked(QToolButton*)));

    ui->actionlayout->addWidget(actionBar);

    connect(Settings::AppSettings->Projects(),SIGNAL(Loaded(QObject*)),this,SLOT(LoadDone(QObject*)));

    Settings::AppSettings->Projects()->Load(Settings::AppSettings->ProjectsFilePath());



    configs= new ConfigurationsWidget (this);



    connect(ui->treeWidget,SIGNAL(ListSelectionChanged(QObject*)),this,SLOT(VisionTreeListSelectionChanged(QObject*)));

}

void MainWindow::VisionTreeListSelectionChanged(QObject* newselection){
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

void MainWindow::LoadDone(QObject* Sender){


    if (dynamic_cast<KPPVisionList<KPPVision>*>(Sender)) {
        ui->treeWidget->AddVisionProjectsModel(Settings::AppSettings->Projects());
    }

}


MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::ActionButtonClicked(QToolButton *buttonClicked)
{
    if (buttonClicked->text()==tr("Configurations")) {

        configs->ToogleState();

    }
    else if (buttonClicked->text()==tr("Exit")) {
        this->close();
    }
}

void MainWindow::bt_Cliked(){

    ui->sideWidget-> toogleMenuState();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    QMainWindow::mousePressEvent(event);
}

//void MainWindow::on_pushButton_clicked()
//{

//    vision= new KPPVision(this);
//    vision->setView(ui->graphicsView);



//}

bool MainWindow::IsLineEdit(const QWidget *widget)
{
    return qobject_cast<const QLineEdit*>(widget) != 0;
}



void MainWindow::focusChanged(QWidget *old, QWidget *now)
{
    //    if (IsLineEdit(now) ){
    //        qDebug()<<"Is line edit";
    //    }
}


void MainWindow::on_pushButton_clicked()
{

    ui->treeWidget->collapseAll();

}

void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
{

}