#include "controller.h"

#include <QtWidgets>

Controller::Controller(QWidget *parent) : QWidget (parent)
{
    model = new Model;
}

void Controller::actionPlay_on_one_computer()
{
    model->startNewGame();
    emit fieldChanged();
}

void Controller::actionSearch_for_an_opponent()
{

}
void Controller::actionPlay_against_bot()
{

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
    qDebug() << "from : " << from;
}

void Controller::mouseReleased(QPoint to)
{
    model->makeMove(mousePressCoordinates, to);
    emit fieldChanged();
    return;
}

Controller::~Controller()
{
    delete model;
}


