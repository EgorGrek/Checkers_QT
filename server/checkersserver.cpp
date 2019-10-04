#include "checkersserver.h"
#include "clienthandler.h"

CheckersServer::CheckersServer(QObject *parent) :
    QTcpServer(parent)
{
}

void CheckersServer::startServer()
{
    if(this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Listening to port " << port << "...";
        DBConnectionProvider *dbConnectionProvider = DBConnectionProvider::getDBConnectionProviderInstance();
        dbConnectionProvider->createConnection();
        dbConnectionProvider->createDB();
    }
    else
    {
        qDebug() << "Could not start server";
    }
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
