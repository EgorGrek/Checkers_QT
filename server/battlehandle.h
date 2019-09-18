#ifndef BUTTLEHANDLE_H
#define BUTTLEHANDLE_H

#include "model.h"
#include "dbconnectionprovider.h"

#include <QThread>
#include <QTcpSocket>

class ButtleHandle: public QThread
{
    Q_OBJECT
public:
    explicit ButtleHandle(QTcpSocket* socketOpponent1, QTcpSocket* socketOpponent2,
                          QObject *parent = nullptr);
    void run();

private:
    void processMessage(const QString &message);

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:

    QTcpSocket *socketOpponent1;
    QTcpSocket *socketOpponent2;

    QString username1;
    QString username2;

    Model model;
    DBConnectionProvider *dbConnectionProvider;
};

#endif // BUTTLEHANDLE_H
