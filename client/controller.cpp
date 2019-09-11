#include "controller.h"

#include <QtWidgets>

Controller::Controller(QWidget *parent) : QObject (parent)
{
    model = new Model;
    serverhandler = new ServerHandler();
    connect(serverhandler, SIGNAL(serverUnavailable()), SIGNAL(serverUnavailable()));
}

void Controller::actionPlay_on_one_computer()
{
    model->startNewGame();
    emit fieldChanged();
}

void Controller::actionSearch_for_an_opponent()
{
    //serverhandler->searchForAnOpponent();
}
void Controller::actionPlay_against_bot()
{
    QMessageBox::information(nullptr, "Message", "This function is not available yet, sorry :(");
}

QVector<QVector<qint8>> Controller::getField()
{
    return model->getField();
}

QString Controller::getLoser()
{
    return model->getLoser();
}
qint8 Controller::getWhoseMove()
{
    return model->getWhoseMove();
}

void Controller::mousePressed(QPoint from)
{
    mousePressCoordinates = from;
}

void Controller::mouseReleased(QPoint to)
{
    model->makeMove(mousePressCoordinates, to);
    emit fieldChanged();
    return;
}

bool Controller::connectToServer()
{
    return serverhandler->connectToServer();
}

Controller::~Controller()
{
    delete model;

    delete serverhandler;
}

void Controller::logIn(QString userName, QString userPassword)
{
    serverhandler->logIn(userName, userPassword);
}

void Controller::createAccount(QString userName, QString userPassword)
{
    serverhandler->createAccount(userName, userPassword);
}

