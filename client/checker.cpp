#include "checker.h"
#include <QtWidgets>

Checker::Checker(CheckersClientWin *pCheckersClientWin, QGraphicsEllipseItem *parent): QGraphicsEllipseItem (parent)
{
    this->pCheckersClientWin = pCheckersClientWin;
}
Checker::~Checker()
{}

void    Checker::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    //this->setOpacity(10);
    this->setZValue(1);
    this->pCheckersClientWin->mausePressed(event->scenePos());
}

void    Checker::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    this->pCheckersClientWin->mauseReleased(event->scenePos());
}
