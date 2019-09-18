#include "clienthandler.h"

ClientHandler::ClientHandler(qintptr ID, QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor = ID;
    this->dbConnectionProvider = DBConnectionProvider::getDBConnectionProviderInstance();
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
        processMessage(str);
        blockSize = 0;
    }
}

void ClientHandler::processMessage(const QString &message)
{
    qint32 messageType = Parser::getMessageType(message);

    if(messageType == CLIENT_LOGIN)
    {
        QPair<QString, QString> login_password = Parser::parsLogin(message);
        if(login_password.first != "" && login_password.second != "")
        {
            if(!dbConnectionProvider->isCorrectPassword(login_password.first, login_password.second))
            {
                sendToClient("notlogin");
            }
            else
            {
                username = login_password.first;
                sendToClient("oklogin");
            }
        }
    }
    else if(messageType == CLIENT_CREATE)
    {
        QPair<QString, QString> login_password = Parser::parsCreateAcc(message);
        if(login_password.first != "" && login_password.second != "")
        {
            if(dbConnectionProvider->isUserExist(login_password.first))
            {
                sendToClient("notcreate");
            }
            else
            {
                dbConnectionProvider->insertUser(login_password.first, login_password.second);
                qDebug() << login_password;
                sendToClient("okcreate");
            }
        }
        else
        {
            sendToClient("notcreate");
        }
    }
    else if(messageType == UNKNOWN_MESSAGE_TYPE)
    {
        disconnected();
    }
}

void ClientHandler::sendToClient(const QString &data)
{
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


    socket->deleteLater();
    exit(0);
}
