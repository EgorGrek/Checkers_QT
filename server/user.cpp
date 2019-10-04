#include "user.h"

User::User( QObject *parent) : QObject(parent)
{
    dbConnectionProvider = DBConnectionProvider::getDBConnectionProviderInstance();
}

QString User::getUsername()
{
    return username;
}

void User::accceptOpponent(const QString &message)
{
    emit sendToOpponent(message);
}

void User::giveUp(const QString &message)
{
    emit sendToOpponent(message);
}

void User::login(const QString &message)
{
    QPair<QString, QString> login_password = Parser::parsLogin(message);
    if(login_password.first != "" && login_password.second != "")
    {
        if(!dbConnectionProvider->isCorrectPassword(login_password.first, login_password.second))
        {
            emit sendToClient("notlogin");
        }
        else
        {
            username = login_password.first;
            emit sendToClient("oklogin");
        }
    }
}

void User::createAcc(const QString &message)
{
    QPair<QString, QString> login_password = Parser::parsCreateAcc(message);
    if(login_password.first != "" && login_password.second != "")
    {
        if(dbConnectionProvider->isUserExist(login_password.first))
        {
            emit sendToClient("notcreate");
        }
        else
        {
            dbConnectionProvider->insertUser(login_password.first, login_password.second);
            emit sendToClient("okcreate");
        }
    }
    else
    {
        emit sendToClient("notcreate");
    }
}

void User::cameMessageFromOpponent(const QString &message)
{
    emit sendToClient(message);
}

void User::makeMove(const QString &message)
{
    emit sendToOpponent(message);
}

    bool User::isUserLoggedIn()
    {
        return userLoggedIn;
    }
