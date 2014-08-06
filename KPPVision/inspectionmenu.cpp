#include "inspectionmenu.h"
#include "ui_inspectionmenu.h"

InspectionMenu::InspectionMenu(QWidget *parent) :
    KPPAnimatedFrame(parent),
    ui(new Ui::InspectionMenu)
{
    ui->setupUi(this);
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

void InspectionMenu::on_pushButton_clicked()
{
    m_SelectedInspection->Process();
}
