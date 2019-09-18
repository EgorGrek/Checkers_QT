#include "viewcheckers.h"
#include <QGraphicsView>
#include <QtWidgets>

ViewCheckers::ViewCheckers(QGraphicsScene* pScene, QWidget* pwgt) : QGraphicsView(pScene, pwgt)
{
}

void ViewCheckers::slotZoomIn()
{
    scale(1.1, 1.1);
}
void ViewCheckers::slotZoomOut()
{
    scale(1/1.1, 1/1.1);
}

void ViewCheckers::wheelEvent(QWheelEvent * event)
{
    if(event->modifiers() == Qt::CTRL)
    {
        if(event->delta() > 0)
        {
            slotZoomIn();
        }
        else
        {
            slotZoomOut();
        }
    }
    else
    {
        QGraphicsView::wheelEvent(event);
    }
}
