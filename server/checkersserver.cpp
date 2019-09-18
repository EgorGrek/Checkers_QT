#include "checkersserver.h"
#include "clienthandler.h"

CheckersServer::CheckersServer(QObject *parent) :
    QTcpServer(parent)
{
}

void CheckersServer::startServer()
{
    quint16 port = PORT_NUM;

    if(!this->listen(QHostAddress::Any,port))
    {
        qDebug() << "Could not start server";
    }
    else
    {
        qDebug() << "Listening to port " << port << "...";
    }

    DBConnectionProvider *dbConnectionProvider = DBConnectionProvider::getDBConnectionProviderInstance();
    dbConnectionProvider->createConnection();
    dbConnectionProvider->createDB();
}

void CheckersServer::incomingConnection(qintptr socketDescriptor)
{
    // We have a new connection
    qDebug() << socketDescriptor << " Connecting...";

    ClientHandler *clientThread = new ClientHandler(socketDescriptor, this);

    // connect signal/slot
    // once a thread is not needed, it will be beleted later
    connect(clientThread, SIGNAL(finished()), clientThread, SLOT(deleteLater()));

    clientThread->start();
}
