#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include "servermessageparser.h"

#include <QObject>
#include <QWidget>
#include <QTcpSocket>


class ServerHandler : public QObject
{
    Q_OBJECT
public:
    ServerHandler();
    ~ServerHandler();
    void connectToServer();
    bool isUserLoggedIn();
    QString getUserLogin();
    void acceptOpponent();
    bool isHaveConnectionToServer();
    void searchForAnOpponent();
    void makeMove(QPoint from, QPoint to);
    void giveUp();
    void logOut();
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
    bool userLoggedIn;
    bool haveConnectionToServer;
    QString userLogin;
    QString userPassword;
    QTcpSocket* serverSocket;
    const quint16 port = 1237;
};

#endif // SERVERHANDLER_H
