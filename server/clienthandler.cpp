#include "clienthandler.h"

ClientHandler::ClientHandler(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
}

void ClientHandler::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void ClientHandler::readyRead()
{
    QDataStream in(socket);
    quint16 blockSize = 0;
    QString str;
    for (;;)
    {
        if (!blockSize)
        {
            if (socket->bytesAvailable () < sizeof(quint16))
                break;
            in >> blockSize;
        }

        if (socket->bytesAvailable() < blockSize)
            break;


        in >> str;
        qDebug() << "Client has sent - " + str;
        blockSize = 0;
    }




    //socket->write(Data);
}

void ClientHandler::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}
