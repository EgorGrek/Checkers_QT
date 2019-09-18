#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"
#include "serverhandler.h"

#include <QWidget>
#include <QTcpSocket>



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

    void connectToServer();
    void logIn(QString userName, QString userPassword);
    void createAccount(QString userName, QString userPassword);

private slots:
    void actionSearch_for_an_opponent();
    void actionPlay_against_bot();
    void actionPlay_on_one_computer();
    void processingMessage(const QString&);

signals:
    void fieldChanged();
    void cameServerMessage(const qint32&);
    void serverError(const QString&);

private:
    Model *model;
    ServerHandler *serverhandler;
    QPoint mousePressCoordinates;

};

#endif // CONTROLLER_H
