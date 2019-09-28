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

    bool mousePressed(QPoint from);
    void mouseReleased(QPoint to);

    void signalWhoseMove();
    void startPlayAgainstOpponentOnServer();
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
    void clickedLogIn_OutButton();

signals:
    void fieldChanged();
    void gameOver();
    void cameServerMessage(const qint32&);
    void cameMessage(const QString&);
    void haveInfo(const QString&);
    void serverError(const QString&);
    void userAuthorized(const QString&);

private:
    Model *model;
    ServerHandler *serverhandler;
    QPoint mousePressCoordinates;
    qint8 userColor;
    enum {gameNotStart, onOneComputer, againstBot, againstOpponentOnServer} gameType;

};

#endif // CONTROLLER_H
