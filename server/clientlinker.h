#ifndef CLIENTLINKER_H
#define CLIENTLINKER_H

#include "battlehandler.h"
#include "user.h"

#include <QObject>
#include <QTcpSocket>
#include <QtSql>
#include <QWidget>


class ClientLinker : public QObject
{
    Q_OBJECT

public:
    void startWaitingAnOpponent(User *user);

    static ClientLinker* getClientLinkerInstance()
    {
        static ClientLinker instance;
        return &instance;
    }
private:
    bool connectClientsToBattleHandler(User *user1, User *user2, BattleHandler *battleHandler);

private:
    QMutex mutex;
    QVector<User*> searchingOpponentClients;

private:
    ClientLinker();
};

#endif // CLIENTLINKER_H
