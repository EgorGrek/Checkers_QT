#include "dbconnectionprovider.h"


DBConnectionProvider::DBConnectionProvider(){}
bool DBConnectionProvider::createConnection()
{
    db = QSqlDatabase::addDatabase ( "QPSQL") ;
    db.setDatabaseName("ejuiqnsm");
    db.setUserName ("ejuiqnsm");
    db.setHostName("balarama.db.elephantsql.com");
    db. setPassword ( "********") ;
    if (!db.open())
    {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }
    else
    {
        qDebug() << "ОГО постирония";
    }
     return true;
}
