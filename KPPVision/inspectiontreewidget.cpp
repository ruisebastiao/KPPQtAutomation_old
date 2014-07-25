#include "inspectiontreewidget.h"
#include "qlabel.h"
#include "qcombobox.h"
#include "QHeaderView"
#include "qpushbutton.h"
#include "QVBoxLayout"
#include "kpproottreepushbutton.h"

InspectionTreeWidget::InspectionTreeWidget(QWidget *parent) :
    QTreeWidget(parent)
{

    setRootIsDecorated(false);

/////Source Name
    QTreeWidgetItem *item_sourcename=new QTreeWidgetItem(0);
    item_sourcename->setDisabled(true);
    QFrame *frame_sourcename=new QFrame();
    frame_sourcename->setAutoFillBackground(false);
    frame_sourcename->setFrameShape(QFrame::NoFrame);
    QVBoxLayout *layout_sourcename= new QVBoxLayout();

    KPPRootTreePushButton *bt_sourcename= new KPPRootTreePushButton("Capture Source",item_sourcename);
    bt_sourcename->setMinimumHeight(10);
    layout_sourcename->addWidget(bt_sourcename);
    frame_sourcename->setLayout(layout_sourcename);
//////////////

    QTreeWidgetItem *item_type=new QTreeWidgetItem(0);
    item_sourcename->addChild(item_type);


    QPushButton *bt_type= new QPushButton("Capture Type");
    bt_type->setMinimumHeight(10);



    addTopLevelItem(item_sourcename);

    setItemWidget(item_sourcename,0,frame_sourcename);


    QComboBox* cb1=new QComboBox();
    //  cb1->addItems(*slist);

    setItemWidget(item_type,0,bt_type);
    setItemWidget(item_type,1,cb1);


    QTreeWidgetItem *item_sourcetype=new QTreeWidgetItem(0);
    item_type->addChild(item_sourcetype);

    QTreeWidget *source_tree= new QTreeWidget();
    source_tree->setAutoFillBackground(true);
    setItemWidget(item_sourcetype,0,source_tree);


    header()->resizeSection(0, 150);
    item_sourcetype->setFirstColumnSpanned(true);
    item_sourcename->setFirstColumnSpanned(true);
}


