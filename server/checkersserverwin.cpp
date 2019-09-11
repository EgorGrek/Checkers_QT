#include "checkersserverwin.h"
#include "ui_checkersserverwin.h"

CheckersServerWin::CheckersServerWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CheckersServerWin)
{
    ui->setupUi(this);
    checkersServer = new CheckersServer();
    checkersServer->startServer();
}

CheckersServerWin::~CheckersServerWin()
{
    delete checkersServer;
    delete ui;
}
