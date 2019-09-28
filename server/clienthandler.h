#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include "dbconnectionprovider.h"
#include "model.h"
#include "controller.h"

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

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();
    void sendToClient(const QString &data);

private:
    qintptr socketDescriptor;
    QTcpSocket *socket;
    Controller *controller;

};

#endif // CLIENTHANDLER_H
