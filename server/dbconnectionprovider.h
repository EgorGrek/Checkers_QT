#ifndef DBCONNECTIONPROVIDER_H
#define DBCONNECTIONPROVIDER_H

#include <QtSql>

class DBConnectionProvider
{
public:
    bool createConnection();

    static DBConnectionProvider* getDBConnectionProviderInstance()
    {
        static DBConnectionProvider instance;
        return &instance;
    }

private:
    DBConnectionProvider();

private:
    QSqlDatabase db;

};

#endif // DBCONNECTIONPROVIDER_H
