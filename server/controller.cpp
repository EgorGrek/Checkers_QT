#include "controller.h"

Controller::Controller()
{
    user = new User();
    clientLinker = ClientLinker::getClientLinkerInstance();
    connect(user, SIGNAL(sendToClient(const QString&)), this, SIGNAL(sendToClient(const QString&)), Qt::DirectConnection);
}

void Controller::processMessage(const QString &message)
{
    qint32 messageType = Parser::getMessageType(message);

    if(messageType == CLIENT_LOGIN)
    {
        user->login(message);
    }
    else if(messageType == CLIENT_CREATE)
    {
        user->createAcc(message);
    }
    else if(messageType == CLIENT_STEP)
    {
        user->makeMove(message);
    }
    else if(messageType == CLIENT_SEARCHING_OPPONENT)
    {
        clientLinker->startWaitingAnOpponent(user);
    }
    else if(messageType == CLIENT_READY)
    {
        user->accceptOpponent(message);
    }
    else if(messageType == CLIENT_GIVE_UP)
    {
        user->giveUp(message);
    }
    else if(messageType == UNKNOWN_MESSAGE_TYPE)
    {

    }
}
