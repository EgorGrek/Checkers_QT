#include "checkersserverwin.h"
#include "dbconnectionprovider.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CheckersServerWin w;
    w.show();
    return app.exec();
}
