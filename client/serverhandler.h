#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include "parser.h"

#include <QObject>
#include <QWidget>
#include <QTcpSocket>

#define PORT_NUM 1237

class ServerHandler : public QObject
{
    Q_OBJECT
public:
    ServerHandler();
    ~ServerHandler();
    void connectToServer();
    bool isUserAuthorized();
    QString getUserLogin();
    void acceptOpponent();
    bool isHaveConnectionToServer();
    void searchForAnOpponent();
    void makeMove(QPoint from, QPoint to);
    void giveUp();
    void logIn(QString userName, QString userPassword);
    void createAccount(QString userName, QString userPassword);

private:
    void sendToServer(const QString &data);
    void processMessage(const QString &message);

signals:
    void serverError(const QString&);
    void messageCame(const QString&);

private slots:

    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotConnected();


private:
    bool userAuthorized;
    bool haveConnectionToServer;
    QString userLogin;
    QTcpSocket* serverSocket;
};

#endif // SERVERHANDLER_H
