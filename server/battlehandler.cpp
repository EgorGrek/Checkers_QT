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
    QThread::msleep(10000); // wait 1/6 minute until the opponents agree

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

void BattleHandler::processMessage(const QString &message, const qint8 &playerColor)
{
    qint32 messageType = Parser::getMessageType(message);
    qDebug() << "BattleHandler" << message;
    if(messageType == CLIENT_STEP)
    {
        // TODO check is move correct
        if(playerColor == WHITEPLAYER)
        {
            emit messageForUserBlack(message);
        }
        else if (playerColor == BLACKPLAYER)
        {
            emit messageForUserWhite(message);
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
    }
    else
    {
    }
}
