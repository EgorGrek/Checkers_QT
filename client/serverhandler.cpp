#include "serverhandler.h"

ServerHandler::ServerHandler()
{
    serverSocket = new QTcpSocket(this);

}

 bool ServerHandler::connectToServer()
 {
     serverSocket->connectToHost("localhost", PORT_NUM);
     if(serverSocket->waitForConnected())
     {
        return true;
     }
     else
     {
         emit serverUnavailable();
         return false;
     }
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

 ServerHandler::~ServerHandler()
 {
     delete serverSocket;
 }
