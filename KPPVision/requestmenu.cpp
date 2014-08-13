#include "requestmenu.h"
#include "ui_requestmenu.h"

RequestMenu::RequestMenu(QWidget *parent) :
    KPPAnimatedFrame(parent),
    ui(new Ui::RequestMenu)
{
    ui->setupUi(this);

    m_SelectedRequest=0;


}

RequestMenu::~RequestMenu()
{
    delete ui;
}
Vision::Request *RequestMenu::SelectedRequest()
{
    return m_SelectedRequest;
}

void RequestMenu::setSelectedRequest(Vision::Request *SelectedRequest)
{
    m_SelectedRequest = SelectedRequest;
}



void RequestMenu::on_bt_processrequest_clicked()
{
    if(m_SelectedRequest!=0){
        m_SelectedRequest->SelectedInspection()->SelectedROI()->Process();
    }
}
