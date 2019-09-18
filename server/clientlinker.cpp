#include "clientlinker.h"

ClientLinker::ClientLinker()
{

}

void ClientLinker::startWaitingAnOpponent(QTcpSocket *clientSocket)
{
    QMutexLocker locker(&mutex);
    if(searchingOpponentClients.empty())
    {
        searchingOpponentClients.append(clientSocket);
    }
    else
    {
        if(searchingOpponentClients[0]->isOpen())
        {
            ButtleHandle *battleThread =
                    new ButtleHandle(searchingOpponentClients[0], clientSocket, this);

            connect(battleThread, SIGNAL(finished()), battleThread, SLOT(deleteLater()));

            battleThread->start();
        }
    }
}

