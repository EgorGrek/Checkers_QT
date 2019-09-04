#ifndef CHECKERQUEEN_H
#define CHECKERQUEEN_H


#include "checkersclientwin.h"

#include <QtWidgets>

class CheckerQueen: public QGraphicsItemGroup
{
public:
    CheckerQueen(CheckersClientWin *pCheckersClientWin, QGraphicsItemGroup *parent = nullptr);
    ~CheckerQueen() override;

private:
    virtual void    mousePressEvent ( QGraphicsSceneMouseEvent * event ) override;
    virtual void    mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ) override;

    CheckersClientWin *pCheckersClientWin;

};

#endif // CHECKERQUEEN_H
