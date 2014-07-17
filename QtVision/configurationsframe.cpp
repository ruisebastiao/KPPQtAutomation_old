#include "configurationsframe.h"
#include "ui_configurationsframe.h"

ConfigurationsFrame::ConfigurationsFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::ConfigurationsFrame)
{

    setWindowFlags(Qt::Window);
    ui->setupUi(this);

    //show();
    //move(parent->width()/2+width()/2,parent->height()/2);
}

ConfigurationsFrame::~ConfigurationsFrame()
{
    delete ui;
}

void ConfigurationsFrame::resizeEvent(QResizeEvent *event)
{
    //event->
    //move(parentWidget()->width()/2,parentWidget()->height()/2);
    QWidget::resizeEvent(event);
}
