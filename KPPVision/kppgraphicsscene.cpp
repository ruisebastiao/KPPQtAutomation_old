#include "kppgraphicsscene.h"
#include "QGraphicsItemGroup"
#include "qpainter.h"
#include "qdebug.h"

KPPGraphicsScene::KPPGraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    setSceneRect(0,0,0,0);
}


void KPPGraphicsScene::drawForeground(QPainter *painter, const QRectF &rect)
{


    QGraphicsScene::drawForeground(painter,rect);

     painter->setPen(QPen(Qt::darkGray, 0, Qt::DashDotLine));
    int num=selectedItems().count();

    if(num>1){
        QGraphicsItem* item= selectedItems().at(0);

        if(item->parentItem()!=0){
            painter->drawRect(item->parentItem()->childrenBoundingRect());
        }
    }


}
