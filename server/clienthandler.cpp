#include "clienthandler.h"

ClientHandler::ClientHandler(qintptr ID, QObject *parent) :
    QThread(parent), controller(nullptr)
{
    this->socketDescriptor = ID;
}

void ClientHandler::run()
{
    // thread starts here
    qDebug() << "ClientThread started";

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
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()), Qt::DirectConnection);

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";

    controller = new Controller();
    connect(controller, SIGNAL(sendToClient(const QString&)), this, SLOT(sendToClient(const QString&)), Qt::DirectConnection);
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
        processMessage(str);
        blockSize = 0;
    }
}

void ClientHandler::processMessage(const QString &message)
{
    controller->processMessage(message);
}

void ClientHandler::sendToClient(const QString &data)
{
    qDebug() << data;
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);


    out << quint16(0)  << data;
    out.device()->seek(0);
    arrBlock.size();
    out << quint16(arrBlock.size() - quint16(sizeof(quint16)));

    socket->write(arrBlock);
}

void ClientHandler::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";
    delete controller;
    socket->deleteLater();
    exit(0);
}
