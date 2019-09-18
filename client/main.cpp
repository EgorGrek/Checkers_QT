#include "checkersclientwin.h"
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSize winSize = app.screens()[0]->size();
    CheckersClientWin w(winSize);
    return app.exec();

}
