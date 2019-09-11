#include "controller.h"

#include <QtWidgets>

Controller::Controller(QWidget *parent) : QObject (parent)
{
    userAuthorized = false;
    model = new Model;
    serverSocket = nullptr;
    registrationWin = nullptr;
}

void Controller::actionPlay_on_one_computer()
{
    model->startNewGame();
    emit fieldChanged();
}

void Controller::actionSearch_for_an_opponent()
{
    serverSocket = new QTcpSocket(this);
    serverSocket->connectToHost("localhost", PORT_NUM);
    if(serverSocket->waitForConnected())
    {
        RegistrationWin *registrationWin = new RegistrationWin();
        registrationWin->setModal(true);
        registrationWin->show();
        registrationWin->reject();
    }
    else
    {
        QMessageBox::information(nullptr, "Message", "Cannot connect to server,\n try again later :(");
    }
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

Controller::~Controller()
{
    if(serverSocket->isOpen())
    {
        serverSocket->close();
    }
    delete model;
    delete serverSocket;
    delete registrationWin;
}


