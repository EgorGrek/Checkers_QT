#ifndef CHECKER_H
#define CHECKER_H
#include "checkersclientwin.h"

#include <QtWidgets>

class Checker: public QGraphicsEllipseItem
{
public:
    Checker(CheckersClientWin *pCheckersClientWin, QGraphicsEllipseItem *parent = nullptr);
    ~Checker() override;

private:
    virtual void    mousePressEvent ( QGraphicsSceneMouseEvent * event ) override;
    virtual void    mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ) override;

    CheckersClientWin *pCheckersClientWin;

};

#endif // CHECKER_H
