#include "model.h"
#include <QVector>
#include <QtWidgets>
#include <QtGlobal>
Model::Model() :field(8, QVector<qint8>(8, EMPTYCELL)), whoseMove(WHITEPLAYER), loser("")
{
}

QVector<QVector<qint8>> Model::getField()
{
    return field;
}

qint8 Model::getWhoseMove()
{
    return whoseMove;
}

void Model::setWhoseMove(bool whoseMove)
{
    this->whoseMove = whoseMove;
}

QVector<QPoint> Model::getCheckersBetween(QPoint first, QPoint second)
{
    QVector<QPoint> checkersBetween;
    qint32 x_increment = second.x() - first.x();
    x_increment /= qAbs(x_increment);
    qint32 y_increment = second.y() - first.y();
    y_increment /= qAbs(y_increment);

    for(qint32 y = first.y() + y_increment, x = first.x() + x_increment;
        y != second.y() && x != second.x();
        y += y_increment, x += x_increment)
    {
        if(field[y][x] != EMPTYCELL)
        {
            checkersBetween.append(QPoint(x, y));
        }

    }
    return checkersBetween;
}

void Model::removeKilledChecker()
{
    for(qint32 i = field.size() - 1; i >= 0; --i)
    {
        for(qint32 j = field[i].size() - 1; j >= 0; --j)
        {
            if(field[i][j] == KILLEDCHECKER)
                field[i][j] = EMPTYCELL;
        }
    }
}

bool Model::transformToQueen(QPoint unit)
{
    if(field[unit.y()][unit.x()] == WHITEUNIT && unit.y() == 0)
    {
        field[unit.y()][unit.x()] = WHITEQUEEN;
        return true;
    }
    else if(field[unit.y()][unit.x()] == BLACKUNIT && unit.y() == 7)
    {
        field[unit.y()][unit.x()] = BLACKQUEEN;
        return true;
    }
    else
    {
        return false;
    }
}

bool Model::makeMove(QPoint from, QPoint to)
{
    qint8 moveType = getMoveType(from, to);

    if(moveType == WRONGMOVE)
    {
        return false;
    }
    else
    {
        field[to.y()][to.x()] = field[from.y()][from.x()];
        field[from.y()][from.x()] = EMPTYCELL;
        if(moveType == HIT)
        {
            QVector<QPoint> checkersBetween = getCheckersBetween(from, to);
            field[checkersBetween[0].y()][checkersBetween[0].x()] = KILLEDCHECKER;
            if(getAvailableToHitCells(to).empty())
            {
                changePlayer();
                removeKilledChecker();

            }
        }
        else
        {
            changePlayer();
        }
        transformToQueen(to);
        if(isGameOver())
        {
            if(whoseMove == WHITEPLAYER)
            {
                loser = "WHITEPLAYER";
            }
            else if(whoseMove == BLACKPLAYER)
            {
                loser = "BLACKPLAYER";
            }
            whoseMove = NOBODY;
        }
    }
    return true;
}

void Model::createStartField()
{

    int indexI = 0;
    bool indexJ = false;
    for(QVector<qint8> &i: field)
    {
        for(qint8 &j : i)
        {
            if(indexI == 0 || indexI == 1 || indexI == 2)
            {
                if(indexJ)
                    j = BLACKUNIT;
            }
            else if(indexI == 5 || indexI == 6 || indexI == 7)
            {
                if(indexJ)
                    j = WHITEUNIT;
            }
            indexJ = !indexJ;
        }
        ++indexI;
        indexJ = !indexJ;
    }
}

qint8 Model::getMoveType(QPoint from, QPoint to)
{
    if(from.x() > 7 || from.x() < 0 ||
            to.x() > 7 || to.x() < 0 ||
            from.y() > 7 || from.y() < 0 ||
            to.y() > 7 || to.y() < 0)
    {
        return WRONGMOVE;
    }
    if((field[from.y()][from.x()] == WHITEUNIT ||  field[from.y()][from.x()] == WHITEQUEEN) &&
            whoseMove != WHITEPLAYER)
    {
        return WRONGMOVE;
    }
    if((field[from.y()][from.x()] == BLACKUNIT ||  field[from.y()][from.x()] == BLACKQUEEN) &&
            whoseMove != BLACKPLAYER)
    {
        return WRONGMOVE;
    }

    QVector<QPoint> availableToHitCells = getAvailableToHitCells(from);
    if(availableToHitCells.empty())
    {
        QVector<QPoint> anyoneAvailableToHitCells;

        for(qint32 i = field.size() - 1; i >= 0; --i)
        {
            for(qint32 j = field[i].size() - 1; j >= 0; --j)
            {
                if(whoseMove == WHITEPLAYER && (field[i][j] == WHITEUNIT || field[i][j] == WHITEQUEEN))
                    anyoneAvailableToHitCells.append(getAvailableToHitCells(QPoint(j, i)));
                else if(whoseMove == BLACKPLAYER && (field[i][j] == BLACKUNIT || field[i][j] == BLACKQUEEN))
                    anyoneAvailableToHitCells.append(getAvailableToHitCells(QPoint(j, i)));
            }
        }
        if(anyoneAvailableToHitCells.empty())
        {
            QVector<QPoint> availableToMoveCells = getAvailableToMoveCells(from);

            if(availableToMoveCells.contains(to))
            {
                return STEP;
            }
        }
    }
    else
    {
        if(availableToHitCells.contains(to))
        {
            return HIT;
        }
    }
    return WRONGMOVE;

}

QVector<QPoint> Model::getAvailableToHitCells(QPoint from)
{
    QVector<QPoint> availableToHitCells;

    if(field[from.y()][from.x()] == WHITEUNIT)
    {
        if(from.x() - 2 < 0)
        {
            if(from.y() - 2 < 0)
            {
                if(field[from.y() + 1][from.x() + 1] == BLACKUNIT ||
                        field[from.y() + 1][from.x() + 1] == BLACKQUEEN)
                {
                    if(field[from.y () + 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() + 2));
                    }
                }
            }

            else if(from.y() + 2 > 7)
            {
                if(field[from.y() - 1][from.x() + 1] == BLACKUNIT ||
                        field[from.y() - 1][from.x() + 1] == BLACKQUEEN)
                {
                    if(field[from.y() - 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() - 2));
                    }
                }
            }
            else
            {
                if(field[from.y() + 1][from.x() + 1] == BLACKUNIT ||
                        field[from.y() + 1][from.x() + 1] == BLACKQUEEN)
                {
                    if(field[from.y() + 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() + 2));
                    }
                }
                if(field[from.y() - 1][from.x() + 1] == BLACKUNIT ||
                        field[from.y() - 1][from.x() + 1] == BLACKQUEEN)
                {
                    if(field[from.y() - 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() - 2));
                    }
                }
            }
        }
        else if(from.x() + 2 > 7)
        {
            if(from.y() - 2 < 0)
            {
                if(field[from.y() + 1][from.x() - 1] == BLACKUNIT ||
                        field[from.y() + 1][from.x() - 1] == BLACKQUEEN)
                {
                    if(field[from.y() + 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() + 2));
                    }
                }
            }

            else if(from.y() + 2 > 7)
            {
                if(field[from.y() - 1][from.x() - 1] == BLACKUNIT ||
                        field[from.y() - 1][from.x() - 1] == BLACKQUEEN)
                {
                    if(field[from.y() - 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() - 2));
                    }
                }
            }
            else
            {
                if(field[from.y() + 1][from.x() - 1] == BLACKUNIT ||
                        field[from.y() + 1][from.x() - 1] == BLACKQUEEN)
                {
                    if(field[from.y() + 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() + 2));
                    }
                }
                if(field[from.y() - 1][from.x() - 1] == BLACKUNIT ||
                        field[from.y() - 1][from.x() - 1] == BLACKQUEEN)
                {
                    if(field[from.y() - 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() - 2));
                    }
                }
            }
        }
        else
        {
            if(from.y() - 2 < 0)
            {
                if(field[from.y() + 1][from.x() - 1] == BLACKUNIT ||
                        field[from.y() + 1][from.x() - 1] == BLACKQUEEN)
                {
                    if(field[from.y() + 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() + 2));
                    }
                }
                if(field[from.y() + 1][from.x() + 1] == BLACKUNIT ||
                        field[from.y() + 1][from.x() + 1] == BLACKQUEEN)
                {
                    if(field[from.y() + 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() + 2));
                    }
                }
            }

            else if(from.y() + 2 > 7)
            {
                if(field[from.y() - 1][from.x() - 1] == BLACKUNIT ||
                        field[from.y() - 1][from.x() - 1] == BLACKQUEEN)
                {
                    if(field[from.y() - 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() - 2));
                    }
                }
                if(field[from.y() - 1][from.x() + 1] == BLACKUNIT ||
                        field[from.y() - 1][from.x() + 1] == BLACKQUEEN)
                {
                    if(field[from.y() - 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() - 2));
                    }
                }
            }
            else
            {
                if(field[from.y() + 1][from.x() - 1] == BLACKUNIT ||
                        field[from.y() + 1][from.x() - 1] == BLACKQUEEN)
                {
                    if(field[from.y() + 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() + 2));
                    }
                }
                if(field[from.y() + 1][from.x() + 1] == BLACKUNIT ||
                        field[from.y() + 1][from.x() + 1] == BLACKQUEEN)
                {
                    if(field[from.y() + 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() + 2));
                    }
                }
                if(field[from.y() - 1][from.x() - 1] == BLACKUNIT ||
                        field[from.y() - 1][from.x() - 1] == BLACKQUEEN)
                {
                    if(field[from.y() - 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() - 2));
                    }
                }
                if(field[from.y() - 1][from.x() + 1] == BLACKUNIT ||
                        field[from.y() - 1][from.x() + 1] == BLACKQUEEN)
                {
                    if(field[from.y() - 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() - 2));
                    }
                }
            }
        }
    }
    else if(field[from.y()][from.x()] == BLACKUNIT)
    {
        if(from.x() - 2 < 0)
        {
            if(from.y() - 2 < 0)
            {
                if(field[from.y() + 1][from.x() + 1] == WHITEUNIT ||
                        field[from.y() + 1][from.x() + 1] == WHITEQUEEN)
                {
                    if(field[from.y() + 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() + 2));
                    }
                }
            }

            else if(from.y() + 2 > 7)
            {
                if(field[from.y() - 1][from.x() + 1] == WHITEUNIT ||
                        field[from.y() - 1][from.x() + 1] == WHITEQUEEN)
                {
                    if(field[from.y() - 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() - 2));
                    }
                }
            }
            else
            {
                if(field[from.y() + 1][from.x() + 1] == WHITEUNIT ||
                        field[from.y() + 1][from.x() + 1] == WHITEQUEEN)
                {
                    if(field[from.y() + 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() + 2));
                    }
                }
                if(field[from.y() - 1][from.x() + 1] == WHITEUNIT ||
                        field[from.y() - 1][from.x() + 1] == WHITEQUEEN)
                {
                    if(field[from.y() - 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() - 2));
                    }
                }
            }
        }
        else if(from.x() + 2 > 7)
        {
            if(from.y() - 2 < 0)
            {
                if(field[from.y() + 1][from.x() - 1] == WHITEUNIT ||
                        field[from.y() + 1][from.x() - 1] == WHITEQUEEN)
                {
                    if(field[from.y() + 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() + 2));
                    }
                }
            }

            else if(from.y() + 2 > 7)
            {
                if(field[from.y() - 1][from.x() - 1] == WHITEUNIT ||
                        field[from.y() - 1][from.x() - 1] == WHITEQUEEN)
                {
                    if(field[from.y() - 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() - 2));
                    }
                }
            }
            else
            {
                if(field[from.y() + 1][from.x() - 1] == WHITEUNIT ||
                        field[from.y() + 1][from.x() - 1] == WHITEQUEEN)
                {
                    if(field[from.y() + 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() + 2));
                    }
                }
                if(field[from.y() - 1][from.x() - 1] == WHITEUNIT ||
                        field[from.y() - 1][from.x() - 1] == WHITEQUEEN)
                {
                    if(field[from.y() - 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() - 2));
                    }
                }
            }
        }
        else
        {
            if(from.y() - 2 < 0)
            {
                if(field[from.y() + 1][from.x() - 1] == WHITEUNIT ||
                        field[from.y() + 1][from.x() - 1] == WHITEQUEEN)
                {
                    if(field[from.y() + 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() + 2));
                    }
                }
                if(field[from.y() + 1][from.x() + 1] == WHITEUNIT ||
                        field[from.y() + 1][from.x() + 1] == WHITEQUEEN)
                {
                    if(field[from.y() + 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() + 2));
                    }
                }
            }

            else if(from.y() + 2 > 7)
            {
                if(field[from.y() - 1][from.x() - 1] == WHITEUNIT ||
                        field[from.y() - 1][from.x() - 1] == WHITEQUEEN)
                {
                    if(field[from.y() - 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() - 2));
                    }
                }
                if(field[from.y() - 1][from.x() + 1] == WHITEUNIT ||
                        field[from.y() - 1][from.x() + 1] == WHITEQUEEN)
                {
                    if(field[from.y() - 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() - 2));
                    }
                }
            }
            else
            {
                if(field[from.y() + 1][from.x() - 1] == WHITEUNIT ||
                        field[from.y() + 1][from.x() - 1] == WHITEQUEEN)
                {
                    if(field[from.y() + 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() + 2));
                    }
                }
                if(field[from.y() + 1][from.x() + 1] == WHITEUNIT ||
                        field[from.y() + 1][from.x() + 1] == WHITEQUEEN)
                {
                    if(field[from.y() + 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() + 2));
                    }
                }
                if(field[from.y() - 1][from.x() - 1] == WHITEUNIT ||
                        field[from.y() - 1][from.x() - 1] == WHITEQUEEN)
                {
                    if(field[from.y() - 2][from.x() - 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() - 2, from.y() - 2));
                    }
                }
                if(field[from.y() - 1][from.x() + 1] == WHITEUNIT ||
                        field[from.y() - 1][from.x() + 1] == WHITEQUEEN)
                {
                    if(field[from.y() - 2][from.x() + 2] == EMPTYCELL)
                    {
                        availableToHitCells.append(QPoint(from.x() + 2, from.y() - 2));
                    }
                }
            }
        }
    }
    else if(field[from.y()][from.x()] == WHITEQUEEN)
    {
        qint32 y_upper_diagonal = -1, x_upper_diagonal = -1;

        qint32 min_axis = qMin(from.y(), from.x());
        qint32 max_axis = qMax(from.y(), from.x());

        if(min_axis == from.y())
        {
            y_upper_diagonal = 0;
            x_upper_diagonal = max_axis - min_axis;
        }
        else if(min_axis == from.x())
        {
            x_upper_diagonal = 0;
            y_upper_diagonal = max_axis - min_axis;
        }
        for (qint32 i = 0; i + max_axis - min_axis  < 8; ++i)
        {
            if(field[y_upper_diagonal + i][x_upper_diagonal + i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(x_upper_diagonal + i, y_upper_diagonal + i));

                if(checkersBetween.size() == 1)
                {
                    if(field[checkersBetween[0].y()][checkersBetween[0].x()] == BLACKUNIT ||
                            field[checkersBetween[0].y()][checkersBetween[0].x()] == BLACKQUEEN)
                    {
                        availableToHitCells.append(QPoint(x_upper_diagonal + i, y_upper_diagonal + i));
                    }
                }
            }
        }

        for (qint32 i = from.x(), j = from.y(); i < 8 && j >= 0; ++i, --j)
        {
            if(field[j][i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(i, j));

                if(checkersBetween.size() == 1)
                {
                    if(field[checkersBetween[0].y()][checkersBetween[0].x()] == BLACKUNIT ||
                            field[checkersBetween[0].y()][checkersBetween[0].x()] == BLACKQUEEN)
                    {
                        availableToHitCells.append(QPoint(i, j));
                    }
                }
            }
        }

        for (qint32 i = from.x(), j = from.y(); i >= 0 && j < 8; --i, ++j)
        {
            if(field[j][i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(i, j));

                if(checkersBetween.size() == 1)
                {
                    if(field[checkersBetween[0].y()][checkersBetween[0].x()] == BLACKUNIT ||
                            field[checkersBetween[0].y()][checkersBetween[0].x()] == BLACKQUEEN)
                    {
                        availableToHitCells.append(QPoint(i, j));
                    }
                }
            }
        }
    }
    else if(field[from.y()][from.x()] == BLACKQUEEN)
    {
        qint32 y_upper_diagonal = -1, x_upper_diagonal = -1;

        qint32 min_axis = qMin(from.y(), from.x());
        qint32 max_axis = qMax(from.y(), from.x());

        if(min_axis == from.y())
        {
            y_upper_diagonal = 0;
            x_upper_diagonal = max_axis - min_axis;
        }
        else if(min_axis == from.x())
        {
            x_upper_diagonal = 0;
            y_upper_diagonal = max_axis - min_axis;
        }
        for (qint32 i = 0; i + max_axis - min_axis < 8; ++i)
        {
            if(field[y_upper_diagonal + i][x_upper_diagonal + i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(x_upper_diagonal + i, y_upper_diagonal + i));

                if(checkersBetween.size() == 1)
                {
                    if(field[checkersBetween[0].y()][checkersBetween[0].x()] == WHITEUNIT ||
                            field[checkersBetween[0].y()][checkersBetween[0].x()] == WHITEQUEEN)
                    {
                        availableToHitCells.append(QPoint(x_upper_diagonal + i, y_upper_diagonal + i));
                    }
                }
            }
        }

        for (qint32 i = from.x(), j = from.y(); i < 8 && j >= 0; ++i, --j)
        {
            if(field[j][i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(i, j));

                if(checkersBetween.size() == 1)
                {
                    if(field[checkersBetween[0].y()][checkersBetween[0].x()] == WHITEUNIT ||
                            field[checkersBetween[0].y()][checkersBetween[0].x()] == WHITEQUEEN)
                    {
                        availableToHitCells.append(QPoint(i, j));
                    }
                }
            }
        }

        for (qint32 i = from.x(), j = from.y(); i >= 0 && j < 8; --i, ++j)
        {
            if(field[j][i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(i, j));

                if(checkersBetween.size() == 1)
                {
                    if(field[checkersBetween[0].y()][checkersBetween[0].x()] == WHITEUNIT ||
                            field[checkersBetween[0].y()][checkersBetween[0].x()] == WHITEQUEEN)
                    {
                        availableToHitCells.append(QPoint(i, j));
                    }
                }
            }
        }
    }

    return availableToHitCells;

}

QVector<QPoint> Model::getAvailableToMoveCells(QPoint from)
{
    QVector<QPoint> availableToMoveCells;

    if(field[from.y()][from.x()] == WHITEUNIT)
    {
        if(from.x() - 1 < 0)
        {
            if(field[from.y() - 1][from.x() + 1] == EMPTYCELL)
            {
                availableToMoveCells.append(QPoint(from.x() + 1, from.y() - 1));
            }

        }
        else if(from.x() + 1 > 7)
        {
            if(field[from.y() - 1][from.x() - 1] == EMPTYCELL)
            {
                availableToMoveCells.append(QPoint(from.x() - 1, from.y() - 1));
            }
        }
        else
        {
            if(field[from.y() - 1][from.x() + 1] == EMPTYCELL)
            {
                availableToMoveCells.append(QPoint(from.x() + 1, from.y() - 1));
            }
            if(field[from.y() - 1][from.x() - 1] == EMPTYCELL)
            {
                availableToMoveCells.append(QPoint(from.x() - 1, from.y() - 1));
            }
        }
    }
    else if(field[from.y()][from.x()] == BLACKUNIT)
    {
        if(from.x() - 1 < 0)
        {
            if(field[from.y() + 1][from.x() + 1] == EMPTYCELL)
            {
                availableToMoveCells.append(QPoint(from.x() + 1, from.y() + 1));
            }

        }
        else if(from.x() + 1 > 7)
        {
            if(field[from.y() + 1][from.x() - 1] == EMPTYCELL)
            {
                availableToMoveCells.append(QPoint(from.x() - 1, from.y() + 1));
            }
        }
        else
        {
            if(field[from.y() + 1][from.x() + 1] == EMPTYCELL)
            {
                availableToMoveCells.append(QPoint(from.x() + 1, from.y() + 1));
            }
            if(field[from.y() + 1][from.x() - 1] == EMPTYCELL)
            {
                availableToMoveCells.append(QPoint(from.x() - 1, from.y() + 1));
            }

        }
    }
    else if(field[from.y()][from.x()] == WHITEQUEEN ||
            field[from.y()][from.x()] == BLACKQUEEN)
    {
        qint32 y_upper_diagonal = -1, x_upper_diagonal = -1;

        qint32 min_axis = qMin(from.y(), from.x());
        qint32 max_axis = qMax(from.y(), from.x());

        if(min_axis == from.y())
        {
            y_upper_diagonal = 0;
            x_upper_diagonal = max_axis - min_axis;
        }
        else if(min_axis == from.x())
        {
            x_upper_diagonal = 0;
            y_upper_diagonal = max_axis - min_axis;
        }
        for (qint32 i = 0; i + max_axis - min_axis < 8; ++i)
        {
            if(field[y_upper_diagonal + i][x_upper_diagonal + i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(x_upper_diagonal + i, y_upper_diagonal + i));

                if(checkersBetween.size() == 0)
                {
                    availableToMoveCells.append(QPoint(x_upper_diagonal + i, y_upper_diagonal + i));
                }

            }
        }

        for (qint32 i = from.x(), j = from.y(); i < 8 && j >= 0; ++i, --j)
        {
            if(field[j][i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(i, j));

                if(checkersBetween.size() == 1)
                {
                    break;
                }
                availableToMoveCells.append(QPoint(i, j));
            }
        }

        for (qint32 i = from.x(), j = from.y(); i >= 0 && j < 8; --i, ++j)
        {
            if(field[j][i] == EMPTYCELL)
            {
                QVector<QPoint> checkersBetween =
                        getCheckersBetween(from, QPoint(i, j));

                if(checkersBetween.size() == 1)
                {
                    break;
                }
                availableToMoveCells.append(QPoint(i, j));
            }
        }
    }
    return availableToMoveCells;
}

void Model::changePlayer()
{
    if(whoseMove == WHITEPLAYER)
    {
        whoseMove = BLACKPLAYER;
    }
    else if(whoseMove == BLACKPLAYER)
    {
        whoseMove = WHITEPLAYER;
    }
}

bool Model::isGameOver()
{
    if(whoseMove == WHITEPLAYER)
    {
        for(qint8 i = 0; i < 8; ++i)
        {
            for(qint8 j = 0; j < 8; ++j)
            {
                if(field[i][j] == WHITEUNIT || field[i][j] == WHITEQUEEN)
                {
                    if(getAvailableToHitCells(QPoint(j, i)).empty())
                    {
                        if(!getAvailableToMoveCells(QPoint(j, i)).empty())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }
    else if(whoseMove == BLACKPLAYER)
    {
        for(qint8 i = 0; i < 8; ++i)
        {
            for(qint8 j = 0; j < 8; ++j)
            {
                if(field[i][j] == BLACKUNIT || field[i][j] == BLACKQUEEN)
                {
                    if(getAvailableToHitCells(QPoint(j, i)).empty())
                    {
                        if(!getAvailableToMoveCells(QPoint(j, i)).empty())
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

QString Model::getLoser()
{
    return loser;
}

qint8 Model::getCellColor(QPoint cellCoord)
{
    if(field[cellCoord.y()][cellCoord.x()] == WHITEUNIT ||
            field[cellCoord.y()][cellCoord.x()] == WHITEQUEEN)
    {
        return WHITEPLAYER;
    }
    else if(field[cellCoord.y()][cellCoord.x()] == BLACKUNIT ||
            field[cellCoord.y()][cellCoord.x()] == BLACKQUEEN)
    {
        return BLACKPLAYER;
    }
    else
    {
        return EMPTYCELL;
    }
}

void Model::startNewGame()
{
    loser = "";
    whoseMove = WHITEPLAYER;
    field.fill(QVector<qint8>(8, EMPTYCELL));
    createStartField();
}
