#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QWidget>
#include <QThread>
#include <QTcpSocket>


class ClientHandler: public QThread
{
Q_OBJECT
public:
    explicit ClientHandler(qintptr ID, QObject *parent = nullptr);

    void run();

signals:
    void error(QTcpSocket::SocketError socketerror);

public slots:
    void readyRead();
    void disconnected();

private:
    QTcpSocket *socket;
    qintptr socketDescriptor;

};

#endif // CLIENTHANDLER_H
