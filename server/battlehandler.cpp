#include "battlehandler.h"

BattleHandler::BattleHandler(User *userWhite, User *userBlack, QObject *parent) : QThread(parent)
{
    this->userWhite = userWhite;
    this->userBlack = userBlack;
    userWhiteReady = false;
    userBlackReady = false;
}

void BattleHandler::run()
{
    qDebug() << "BattleThread started";

    emit messageForUserWhite("areyouready:" + userBlack->getUsername());
    emit messageForUserBlack("areyouready:" + userWhite->getUsername());
    //    this->dbConnectionProvider = DBConnectionProvider::getDBConnectionProviderInstance();
    sleeper.sleep(60000); // wait 1 minute until the opponents agree

    if(userWhiteReady && userBlackReady)
    {
        model.startNewGame();
        emit messageForUserWhite("startwhite");
        emit messageForUserBlack("startblack");
        exec();
    }
    else
    {
        emit messageForUserWhite("notstart");
        emit messageForUserBlack("notstart");
        exit(0);
    }
}

void BattleHandler::readyReadUserWhite(const QString &message)
{
    processMessage(message, WHITEPLAYER);
}

void BattleHandler::readyReadUserBlack(const QString &message)
{
    processMessage(message, BLACKPLAYER);
}

void BattleHandler::disconnectedUserWhite()
{

}

void BattleHandler::disconnectedUserBlack()
{

}

void BattleHandler::sendToOppositeUser(const QString &message, const qint8 &playerColor)
{
    if(playerColor == WHITEPLAYER)
    {
        emit messageForUserBlack(message);
    }
    else if (playerColor == BLACKPLAYER)
    {
        emit messageForUserWhite(message);
    }
}


void BattleHandler::processMessage(const QString &message, const qint8 &playerColor)
{
    qint32 messageType = Parser::getMessageType(message);
    qDebug() << "BattleHandler" << message;
    if(messageType == CLIENT_STEP)
    {
        QPair<QPoint, QPoint> step =  Parser::parsStep(message);
        if(model.makeMove(step.first, step.second, playerColor))
        {
            sendToOppositeUser(message, playerColor);
            sendToOppositeUser("okstep", playerColor);
        }
        else
        {
            if(playerColor == WHITEPLAYER)
            {
                emit messageForUserWhite("notstep");
            }
            else if (playerColor == BLACKPLAYER)
            {
                emit messageForUserBlack("notstep");
            }
        }
    }
    else if(messageType == CLIENT_READY)
    {
        if(playerColor == WHITEPLAYER)
        {
            userWhiteReady = true;
            qDebug() << "userWhiteReady = true;";
        }
        else if (playerColor == BLACKPLAYER)
        {
            userBlackReady = true;
            qDebug() << "userBlackReady = true;";
        }

        if(userBlackReady && userWhiteReady)
        {
            sleeper.wake();
        }
    }
    else
    {
        sendToOppositeUser(message, playerColor);
    }
}
