#include "checkersserverwin.h"
#include "dbconnectionprovider.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CheckersServerWin w;
    w.show();

    DBConnectionProvider *test = DBConnectionProvider::getDBConnectionProviderInstance();
    test->createConnection();

    return a.exec();
}
