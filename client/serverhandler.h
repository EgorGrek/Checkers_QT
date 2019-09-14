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
    void connectToServer();
    bool isUserAuthorized();
    void searchForAnOpponent();
    void makeMove(QPoint from, QPoint to);
    void giveUp();
    void logIn(QString userName, QString userPassword);
    void createAccount(QString userName, QString userPassword);

private:
    void sendToServer(const QString &data);

signals:
    void serverError(const QString&);
    void messageCame(const QString&);

private slots:

    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);
    void slotConnected();


private:
    bool userAuthorized;
    QString userName;
    QString userPassword;

    QTcpSocket* serverSocket;
};

#endif // SERVERHANDLER_H
