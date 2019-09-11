#ifndef CHECKERSSERVERWIN_H
#define CHECKERSSERVERWIN_H

#include "checkersserver.h"

#include <QMainWindow>

namespace Ui {
class CheckersServerWin;
}

class CheckersServerWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit CheckersServerWin(QWidget *parent = nullptr);
    ~CheckersServerWin();

private:
    Ui::CheckersServerWin *ui;
    CheckersServer* checkersServer;
};

#endif // CHECKERSSERVERWIN_H
