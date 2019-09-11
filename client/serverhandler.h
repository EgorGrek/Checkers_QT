#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

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
    bool connectToServer();
    bool isUserAuthorized();
    void searchForAnOpponent();
    void makeMove(QPoint from, QPoint to);
    void giveUp();
    void logIn(QString userName, QString userPassword);
    void createAccount(QString userName, QString userPassword);

private:
    void sendToServer(const QString &data);

signals:
    void disconnectedFromServer();
    void serverUnavailable();
    void notLogin(const QString& reason);
    void login();

private:
    bool userAuthorized;
    QString userName;
    QString userPassword;

    QTcpSocket* serverSocket;
};

#endif // SERVERHANDLER_H
