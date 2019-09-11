#ifndef MODEL_H
#define MODEL_H


#include <QObject>
#include <QVector>

#define EMPTYCELL 0
#define WHITEUNIT 1
#define BLACKUNIT 2
#define WHITEQUEEN 3
#define BLACKQUEEN 4
#define KILLEDCHECKER 5

#define WRONGMOVE 0
#define HIT 1
#define STEP 2

#define BLACKPLAYER 0
#define WHITEPLAYER 1
#define NOBODY 2

class Model: public QObject
{
public:
    Model();
    QVector<QVector<qint8>> getField();
    void startNewGame();

    void makeMove(QPoint from, QPoint to);
    qint8 getWhoseMove();

    QString getLoser();

    QVector<QPoint> getAvailableToMoveCells(QPoint from);
    QVector<QPoint> getAvailableToHitCells(QPoint from);
private:
    void createStartField();
    void changePlayer();
    bool transformToQueen(QPoint unit);
    void removeKilledChecker();
    qint8 getMoveType(QPoint from, QPoint to);
    void setWhoseMove(bool whoseMove);
    QVector<QPoint> getCheckersBetween(QPoint first, QPoint second);

    bool isGameOver();

private:
    QVector<QVector<qint8>> field;

    qint8 whoseMove; // white/black/nobody

    QString loser;

};

#endif // MODEL_H
