#ifndef CHECKERSCLIENTWIN_H
#define CHECKERSCLIENTWIN_H

#include "model.h"
#include "controller.h"
#include "viewcheckers.h"

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
    void mausePressed(QPointF mouseCoordinates);
    void mauseReleased(QPointF mouseCoordinates);
    void showLoser();


private:
    QPoint getFieldPosition(QPointF mouseCoordinates);
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:
    void redraw();



private:
    Ui::CheckersClientWin *ui;
    Controller *controller;
    ViewCheckers *pView;


};

#endif // CHECKERSCLIENTWIN_H
