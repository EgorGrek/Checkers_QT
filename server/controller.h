#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "clienthandler.h"

#include <QObject>
#include <QtWidgets>
#include <QTcpServer>
#include <QTcpSocket>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();


};

#endif // CONTROLLER_H
