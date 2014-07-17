#include "crashdialog.h"
#include "ui_crashdialog.h"
#include "qstringlistmodel.h"
#include "kppcommon.h"

CrashDialog::CrashDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CrashDialog)
{

    ui->setupUi(this);

    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowTitleHint) ;
   // setWindowFlags(Qt::Dialog) ;
    setModal(true);
    setStyleSheet(KPPCommon::loadStyleSheet(":/glossy"));
}

CrashDialog::~CrashDialog()
{
    delete ui;
}

void CrashDialog::setMessage(QStringList msgs){


    QStringListModel *model = new QStringListModel(ui->listView);
    model->setStringList(msgs);
    ui->listView->setModel(model);
    ui->listView->AdjustContents(0);
}




void CrashDialog::showEvent(QShowEvent *)
{
    ui->listView->AdjustContents();
}
