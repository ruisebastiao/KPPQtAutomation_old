#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "actionbar.h"
#include "qlineedit.h"
#include "settings.h"
#include "crashdialog.h"

#include "type_traits"
#include "QDesktopWidget"
#include "swipegesturerecognizer.h"


using namespace Vision;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    if(QTouchDevice::devices().count()==0){
        QGestureRecognizer* pRecognizer = new SwipeGestureRecognizer();
        grabGesture(QGestureRecognizer::registerRecognizer(pRecognizer));
    }


    ui->actionlayout->setMargin(0);
    ui->actionlayout->setSizeConstraint(QLayout::SetNoConstraint);

    ActionBar* actionBar=new ActionBar(ui->centralWidget);
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

    visionmodule= new VisionWindow(this);
    ui->modulelayout->addWidget(visionmodule);
    //connect(Settings::AppSettings->Projects(),SIGNAL(Loaded(QObject*)),this,SLOT(LoadDone(QObject*)));



}


void MainWindow::LoadDone(QObject* Sender){


//    if (dynamic_cast<KPPVisionList<KPPVision>*>(Sender)) {
//        ui->treeWidget->AddVisionProjectsModel(Settings::AppSettings->Projects());
//    }

}


MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::ActionButtonClicked(QToolButton *buttonClicked)
{
    if (buttonClicked->text()==tr("Configurations")) {

        visionmodule->toogleModuleSettings();

    }
    else if (buttonClicked->text()==tr("Exit")) {
        this->close();
    }
}

void MainWindow::bt_Cliked(){




}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    QMainWindow::mousePressEvent(event);
}



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



