#ifndef BUTTLEHANDLE_H
#define BUTTLEHANDLE_H

#include "user.h"
#include "model.h"
#include "dbconnectionprovider.h"
#include "wakeablesleep.h"
#include "parser.h"

#include <QThread>
#include <QTcpSocket>

class BattleHandler: public QThread
{
    Q_OBJECT
public:
    explicit BattleHandler(User *userWhite, User *userBlack, QObject *parent = nullptr);
    void run();

private:
    void processMessage(const QString &message, const qint8 &playerColor);
    void sendToOppositeUser(const QString &message, const qint8 &playerColor);

signals:
    void messageForUserWhite(const QString &message);
    void messageForUserBlack(const QString &message);

public slots:
    void readyReadUserWhite(const QString &message);
    void readyReadUserBlack(const QString &message);
    void disconnectedUserWhite();
    void disconnectedUserBlack();

private:

    User *userWhite;
    User *userBlack;
    bool userWhiteReady;
    bool userBlackReady;
    Model model;

    WakeableSleep sleeper;
    DBConnectionProvider *dbConnectionProvider;
};

#endif // BUTTLEHANDLE_H
