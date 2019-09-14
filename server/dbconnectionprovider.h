#ifndef DBCONNECTIONPROVIDER_H
#define DBCONNECTIONPROVIDER_H

#include <QtSql>
#include <QWidget>

class DBConnectionProvider
{
public:
    bool createConnection();

    void closeConnection();


    static DBConnectionProvider* getDBConnectionProviderInstance()
    {
        static DBConnectionProvider instance;
        return &instance;
    }

    void createDB();
    void insertUser(const QString &name, const QString &password);
    bool isUserExist(const QString &name);
    bool isCorrectPassword(const QString &name, const QString &password);

private:
    DBConnectionProvider();

private:

    QMutex mutex;
    QSqlDatabase db;

};

#endif // DBCONNECTIONPROVIDER_H
