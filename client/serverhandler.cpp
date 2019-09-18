#include "serverhandler.h"


ServerHandler::ServerHandler()
{
    userAuthorized = false;
    serverSocket = new QTcpSocket(this);
    connect(serverSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(serverSocket, SIGNAL(readyRead() ), SLOT(slotReadyRead()));
    connect(serverSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT (slotError (QAbstractSocket::SocketError)));

}

void ServerHandler::connectToServer()
{
    serverSocket->connectToHost("localhost", PORT_NUM);
    emit messageCame("connecting");
}

void ServerHandler::logIn(QString userName, QString userPassword)
{
    sendToServer("login:" + userName +":" + userPassword);
}

void ServerHandler::createAccount(QString userName, QString userPassword)
{
    sendToServer("create:" + userName + ":" + userPassword);
}

void ServerHandler::sendToServer(const QString &data)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);


    out << quint16(0)  << data;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - quint16(sizeof(quint16)));

    serverSocket->write(arrBlock);
}

void ServerHandler::slotReadyRead()
{
    QDataStream in(serverSocket);
    qDebug() << "slotReadyRead";
    quint16 blockSize = 0;
    for (;;) {
        if (!blockSize) {
            if (serverSocket->bytesAvailable() < sizeof(quint16))
                break;

            in >> blockSize;
        }
        if (serverSocket->bytesAvailable() < blockSize)
            break;
        QString message;
        in  >> message;
        blockSize = 0;
        processMessage(message);
        emit messageCame(message);

    }
}

void ServerHandler::slotError(QAbstractSocket::SocketError err)
{
    userAuthorized = false;
    QString strError =
            "Error: "+ (err == QAbstractSocket::HostNotFoundError ?
                            "The host was not found." :
                            err == QAbstractSocket::RemoteHostClosedError ?
                                "The remote host is closed." :
                                err == QAbstractSocket::ConnectionRefusedError?
                                    "The connection was refused." :
                                    QString(serverSocket->errorString())
                                    );
    emit serverError(strError);
}

void ServerHandler::slotConnected()
{
    emit messageCame("connected");
    emit messageCame("showRegistrationWin");
}

void ServerHandler::searchForAnOpponent()
{
    if(!serverSocket->isOpen())
    {
        connectToServer();
        return;
    }
    else if(userAuthorized)
    {
        sendToServer("searchopp");
    }
    else
    {
        emit messageCame("showRegistrationWin");
    }
}

void ServerHandler::processMessage(const QString &message)
{
    qDebug() << message;
    qint32 messageType = Parser::getMessageType(message);
    if(messageType == OK_LOGIN || OK_CREATE)
    {
        userAuthorized = true;
    }
}

ServerHandler::~ServerHandler()
{
    delete serverSocket;
}
