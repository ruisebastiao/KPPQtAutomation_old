#include "inspectionmenu.h"
#include "ui_inspectionmenu.h"
#include "QxtWidgets/qxtglobalshortcut.h"

InspectionMenu::InspectionMenu(QWidget *parent) :
    KPPAnimatedFrame(parent),
    ui(new Ui::InspectionMenu)
{
    ui->setupUi(this);
    m_SelectedInspection=0;


    QxtGlobalShortcut* capture_shortcut= new QxtGlobalShortcut(QKeySequence(tr("F3", "Process")),
                              this);

    this->connect(capture_shortcut,SIGNAL(activated()),this,SLOT(on_bt_capture_clicked()));

    QxtGlobalShortcut* capture_process_shortcut= new QxtGlobalShortcut(QKeySequence(tr("F4", "Process")),
                              this);
    this->connect(capture_process_shortcut,SIGNAL(activated()),this,SLOT(on_bt_capture_process_clicked()));


}

InspectionMenu::~InspectionMenu()
{
    delete ui;
}

Vision::Inspection *InspectionMenu::SelectedInspection()
{
    return m_SelectedInspection;
}

void InspectionMenu::setSelectedInspection(Vision::Inspection *SelectedInspection)
{
    m_SelectedInspection = SelectedInspection;

}


void InspectionMenu::on_bt_capture_clicked()
{
    if(m_SelectedInspection!=0)
        m_SelectedInspection->Process(true,false);
}

void InspectionMenu::on_bt_capture_process_clicked()
{
 if(m_SelectedInspection!=0)
    m_SelectedInspection->Process(true,true);
}

void InspectionMenu::on_bt_process_clicked()
{
    if(m_SelectedInspection!=0)
        m_SelectedInspection->Process(false,true);
}

