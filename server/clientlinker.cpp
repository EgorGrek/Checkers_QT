#include "clientlinker.h"

ClientLinker::ClientLinker()
{

}

bool ClientLinker::connectClientsToBattleHandler(User *user1, User *user2,
                                                 BattleHandler *battleHandler)
{
    if(!connect(battleHandler,
                SIGNAL(messageForUserWhite(const QString&)),
                user1,
                SLOT(cameMessageFromOpponent(const QString&))))
    {
        return false;
    }

    if(!connect(battleHandler,
                SIGNAL(messageForUserBlack(const QString&)),
                user2,
                SLOT(cameMessageFromOpponent(const QString&))))
    {
        return false;
    }

    if(!connect(user1,
                SIGNAL(disconnected()),
                battleHandler,
                SLOT(disconnectedUserWhite()), Qt::DirectConnection))
    {
        return false;
    }

    if(!connect(user2,
                SIGNAL(disconnected()),
                battleHandler,
                SLOT(disconnectedUserBlack()), Qt::DirectConnection))
    {
        return false;
    }

    if(!connect(user1,
                SIGNAL(sendToOpponent(const QString&)),
                battleHandler,
                SLOT(readyReadUserWhite(const QString&)), Qt::DirectConnection))
    {
        return false;
    }

    if(!connect(user2,
                SIGNAL(sendToOpponent(const QString&)),
                battleHandler,
                SLOT(readyReadUserBlack(const QString&)), Qt::DirectConnection))
    {
        return false;
    }

    return true;
}

void ClientLinker::startWaitingAnOpponent(User *user)
{
    QMutexLocker locker(&mutex);
    if(searchingOpponentClients.empty())
    {
        searchingOpponentClients.append(user);
    }
    else
    {
        bool foundOpponent = false;
        qint32 numberOpponent = 0;
        BattleHandler *battleHandler;
        for(User*i : searchingOpponentClients)
        {
            battleHandler = new BattleHandler(user, i);
            if(connectClientsToBattleHandler(user, i, battleHandler))
            {
                connect(battleHandler, SIGNAL(finished()), battleHandler, SLOT(deleteLater()));
                battleHandler->start();
                foundOpponent = true;
                break;
            }
            else
            {
                delete battleHandler;
                ++numberOpponent;
            }
        }
        if(foundOpponent)
        {
            searchingOpponentClients.remove(numberOpponent);

        }
        else
        {
            searchingOpponentClients.append(user);
        }
    }
}
