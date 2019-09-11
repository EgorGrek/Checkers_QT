#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "registrationwin.h"

#include <QWidget>
#include <QTcpSocket>

#define PORT_NUM 1237

class Controller: public QObject
{
    Q_OBJECT

public:
    explicit Controller(QWidget *parent = nullptr);
    virtual ~Controller();

    void mousePressed(QPoint from);
    void mouseReleased(QPoint to);

    qint8 getWhoseMove();
    QVector<QVector<qint8>> getField();
    QString getLoser();

private slots:
    void actionSearch_for_an_opponent();
    void actionPlay_against_bot();
    void actionPlay_on_one_computer();

signals:
    void fieldChanged();

private:
    Model *model;
    QTcpSocket* serverSocket;
    RegistrationWin *registrationWin;
    QPoint mousePressCoordinates;
};

#endif // CONTROLLER_H
