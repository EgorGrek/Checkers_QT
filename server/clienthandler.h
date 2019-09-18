#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include "dbconnectionprovider.h"
#include "parser.h"
#include "model.h"

#include <QWidget>
#include <QThread>
#include <QTcpSocket>


class ClientHandler: public QThread
{
Q_OBJECT
public:
    explicit ClientHandler(qintptr ID, QObject *parent = nullptr);
    void run();

private:
    void processMessage(const QString &message);
    void sendToClient(const QString &data);
signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;
    QString username;

    DBConnectionProvider *dbConnectionProvider;

};

#endif // CLIENTHANDLER_H
