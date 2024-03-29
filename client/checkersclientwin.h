#ifndef CHECKERSCLIENTWIN_H
#define CHECKERSCLIENTWIN_H

#include "model.h"
#include "controller.h"
#include "viewcheckers.h"
#include "servermessageparser.h"

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class CheckersClientWin;
}

class CheckersClientWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit CheckersClientWin(QSize winSize, QWidget *parent = nullptr);
    ~CheckersClientWin() override;

    void drawField();
    void drawCheckers();
    bool mausePressed(QPointF mouseCoordinates);
    void mauseReleased(QPointF mouseCoordinates);


private:
    QPoint getFieldPosition(QPointF mouseCoordinates);
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void redraw();
    void showRules();
    void showLoser();
    void showMessage(const QString &message);
    void showInfo(const QString &info);
    void showUserLogin(const QString &login);
    void showWhoseMove(const QString &whoseMove);
    void showOpponentAcceptanceWin(const QString &opponentName);
    void serverError(const QString &err);
    void cameServerMessage(const qint32&);


private:
    Ui::CheckersClientWin *ui;
    Controller *controller;
    ViewCheckers *pView;
    QLabel *userInfo;
    QLabel *userLogin;
    QLabel *whoseMove;
    QPushButton* pcmdLogIn_Out;
    QPushButton* pcmdGiveUp;


};

#endif // CHECKERSCLIENTWIN_H
