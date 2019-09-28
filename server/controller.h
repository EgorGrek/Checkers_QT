#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "user.h"
#include "parser.h"
#include "clientlinker.h"

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    void processMessage(const QString &message);

signals:
    void sendToClient(const QString &message);

private:
    User *user;
    ClientLinker *clientLinker;

};

#endif // CONTROLLER_H
