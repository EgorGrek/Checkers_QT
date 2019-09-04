#include "checkerqueen.h"

#include <QtWidgets>

CheckerQueen::CheckerQueen(CheckersClientWin *pCheckersClientWin, QGraphicsItemGroup *parent): QGraphicsItemGroup (parent)
{
    this->pCheckersClientWin = pCheckersClientWin;
}
CheckerQueen::~CheckerQueen()
{}

void    CheckerQueen::mousePressEvent ( QGraphicsSceneMouseEvent * event )
{
    //this->setOpacity(10);
    this->setZValue(1);
    this->pCheckersClientWin->mausePressed(event->scenePos());
}

void    CheckerQueen::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    this->pCheckersClientWin->mauseReleased(event->scenePos());
}
