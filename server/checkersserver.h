#ifndef CHECKERSSERVER_H
#define CHECKERSSERVER_H


#include "clienthandler.h"
#include "dbconnectionprovider.h"

#include <QTcpServer>

class CheckersServer: public QTcpServer
{
    Q_OBJECT
public:
    explicit CheckersServer(QObject *parent = nullptr);
    void startServer();
signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    const quint16 port = 1237;
};

#endif // CHECKERSSERVER_H
