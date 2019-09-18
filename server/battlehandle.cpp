#include "battlehandle.h"

ButtleHandle::ButtleHandle(QTcpSocket* socketOpponent1, QTcpSocket* socketOpponent2,
                           QObject *parent) : QThread(parent)
{
    this->socketOpponent1 = socketOpponent1;
    this->socketOpponent2 = socketOpponent2;
    this->dbConnectionProvider = DBConnectionProvider::getDBConnectionProviderInstance();
}

void ButtleHandle::run()
{
    // thread starts here
    qDebug() << "BattleThread started";

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socketOpponent1, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socketOpponent1, SIGNAL(disconnected()), this, SLOT(disconnected()));


    connect(socketOpponent2, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socketOpponent2, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    model.startNewGame();
    exec();
}


void ButtleHandle::readyRead()
{
    QDataStream in(socketOpponent1);
    quint16 blockSize = 0;
    QString str;
    for (;;)
    {
        if (!blockSize)
        {
            if (socketOpponent1->bytesAvailable () < sizeof(quint16))
                break;
            in >> blockSize;
        }

        if (socketOpponent1->bytesAvailable() < blockSize)
            break;


        in >> str;
        qDebug() << "Client has sent - " + str;
        blockSize = 0;
    }




    //socket->write(Data);
}

//void ButtleHandle::processMessage(const QString &message)
//{
//    qint32 messageType = Parser::getMessageType(message);
//    if(messageType == CLIENT_STEP)
//    {
//    }
//    else if(messageType == CLIENT_LOGIN)
//    {

//    }
//    else if(messageType == CLIENT_CREATE)
//    {

//    }
//    else if(messageType == UNKNOWN_MESSAGE_TYPE)
//    {
//        disconnected();
//    }
//}

void ButtleHandle::disconnected()
{
    socketOpponent1->deleteLater();
    exit(0);
}
