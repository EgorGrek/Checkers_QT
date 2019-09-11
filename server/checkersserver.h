#ifndef CHECKERSSERVER_H
#define CHECKERSSERVER_H


#include "clienthandler.h"

#include <QTcpServer>

#define PORT_NUM 1237

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
};

#endif // CHECKERSSERVER_H
