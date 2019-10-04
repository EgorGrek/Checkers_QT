#ifndef USER_H
#define USER_H

#include "dbconnectionprovider.h"
#include "parser.h"

#include <QObject>

class User : public QObject
{
    Q_OBJECT

public:
    User(QObject *parent = nullptr);
    QString getUsername();
    void createAcc(const QString &message);
    void login(const QString &message);
    void makeMove(const QString &message);
    void giveUp(const QString &message);
    void accceptOpponent(const QString &message);
    bool isUserLoggedIn();

public slots:
    void cameMessageFromOpponent(const QString &message);

signals:
    void sendToClient(const QString &message);
    void sendToOpponent(const QString &message);
    void disconnected();

private:
    bool userLoggedIn;
    QString username;
    DBConnectionProvider *dbConnectionProvider;
};

#endif // USER_H
