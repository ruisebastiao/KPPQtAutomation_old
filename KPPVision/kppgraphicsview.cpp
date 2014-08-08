#include "kppgraphicsview.h"
#include "QPaintEvent"
#include "QGraphicsItemGroup"

KPPGraphicsView::KPPGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    setInteractive(true);
    setDragMode(QGraphicsView::RubberBandDrag);
    //this->rubberBandRect()
    //scene()->items().at(0)->
}



void KPPGraphicsView::paintEvent(QPaintEvent *e)
{

    QGraphicsView::paintEvent(e);

//    QPainter painter(viewport());

//    if(scene()->selectedItems().count()>1){
//        QGraphicsItemGroup* group= scene()->selectedItems().at(0)->group();
//        if(group!=0){
//            painter.drawRect(group->boundingRect());
//        }
//        ////         group->se
//        //        //scene()->selectedItems()
//        //     }
//    }
//    //     //painter.draw



}
