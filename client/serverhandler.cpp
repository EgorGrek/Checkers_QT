#include "serverhandler.h"


ServerHandler::ServerHandler()
{
    serverSocket = new QTcpSocket(this);
    connect(serverSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(serverSocket, SIGNAL(readyRead() ), SLOT(slotReadyRead()));
    connect(serverSocket, SIGNAL(error(QAЬstractSocket::SocketError)),
            this, SLOT (slotError (QAЬstractSocket: :SocketError)));

}

void ServerHandler::connectToServer()
{
    serverSocket->connectToHost("localhost", PORT_NUM);
    emit messageCame("connecting");
}

void ServerHandler::logIn(QString userName, QString userPassword)
{
    sendToServer("login:" + userName +";" + userPassword);
}

void ServerHandler::createAccount(QString userName, QString userPassword)
{
    sendToServer("create:" + userName + ";" + userPassword);
}

void ServerHandler::sendToServer(const QString &data)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);


    out << quint16(0)  << data;
    out.device()->seek(0);
    arrBlock.size();
    out << quint16(arrBlock.size() - quint16(sizeof(quint16)));

    serverSocket->write(arrBlock);
}

void ServerHandler::slotReadyRead()
{
    QDataStream in(serverSocket);
    quint16 blockSize = 0;
    for (;;) {
        if (!blockSize) {
            if (serverSocket->bytesAvailable() < sizeof(quint16))
                break;

            in >> blockSize;
        }
        if (serverSocket->bytesAvailable() < blockSize)
            break;
        QString str;
        in  >> str;
        blockSize = 0;
        emit messageCame(str);
    }
}

void ServerHandler::slotError(QAbstractSocket::SocketError err)
{
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
}

void ServerHandler::searchForAnOpponent()
{
    if(!serverSocket->isOpen())
    {
        connectToServer();
        emit messageCame("connecting");
        return;
    }
    sendToServer("searchopp");
}

ServerHandler::~ServerHandler()
{
    delete serverSocket;
}
