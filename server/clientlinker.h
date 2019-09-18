#ifndef CLIENTLINKER_H
#define CLIENTLINKER_H

#include "battlehandle.h"

#include <QObject>
#include <QTcpSocket>
#include <QtSql>
#include <QWidget>

class ClientLinker : public QObject
{
    Q_OBJECT

public:
    void startWaitingAnOpponent(QTcpSocket* clientSocket);

    static ClientLinker* getClientLinkerInstance()
    {
        static ClientLinker instance;
        return &instance;
    }
private:
    QMutex mutex;
    QVector<QTcpSocket*> searchingOpponentClients;

private:
    ClientLinker();
};

#endif // CLIENTLINKER_H
