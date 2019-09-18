#include "controller.h"
#include "parser.h"
#include <QtWidgets>

Controller::Controller(QWidget *parent) : QObject (parent)
{
    model = new Model;
    serverhandler = new ServerHandler();
    connect(serverhandler, SIGNAL(serverError(const QString&)), SIGNAL(serverError(const QString&)));
    connect(serverhandler, SIGNAL(messageCame(const QString&)), SLOT(processingMessage(const QString&)));
}

void Controller::actionPlay_on_one_computer()
{
    model->startNewGame();
    emit fieldChanged();
}

void Controller::actionSearch_for_an_opponent()
{
    serverhandler->searchForAnOpponent();
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

void Controller::connectToServer()
{
   serverhandler->connectToServer();
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

void Controller::processingMessage(const QString& message)
{
    qint32 messageType = Parser::getMessageType(message);
    qDebug() << message;
    if(messageType == UNKNOWN_MESSAGE_TYPE)
    {
        emit serverError("Error: We don't understand request from server :(,\n maybe you should update application3");
    }
    else if(messageType == ENEMY_STEP)
    {
        QPair<QPoint, QPoint> from_to_move = Parser::parsStep(message);
        model->makeMove(from_to_move.first, from_to_move.second);
        emit fieldChanged();
    }
    else
    {
        emit cameServerMessage(messageType);
    }
}

