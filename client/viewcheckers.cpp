#include "viewcheckers.h"
#include <QGraphicsView>

ViewCheckers::ViewCheckers(QGraphicsScene* pScene, QWidget* pwgt) : QGraphicsView(pScene, pwgt)
{
}

void ViewCheckers::slotZoomin()
{
    scale(1.1, 1.1);
}
void ViewCheckers::slotZoomOut()
{
    scale(1/1.1, 1/1.1);
}
