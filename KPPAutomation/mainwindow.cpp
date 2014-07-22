#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "actionbar.h"
#include "qlineedit.h"
#include "settings.h"
#include "crashdialog.h"

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


    Settings::AppSettings->Projects()->Load(Settings::AppSettings->ProjectsFilePath());



    configs= new ConfigurationsWidget (this);

    ui->treeWidget->AddVisionProjectsModel(Settings::AppSettings->Projects());
    //ui->treeWidget->getListViewProjects()->setModel(Settings::AppSettings->Projects());
//    IDSCameraConfig *teste= new IDSCameraConfig(this);
//    teste->show();

   // camera=new IDSCamera(this);


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
