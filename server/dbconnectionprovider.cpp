#include "dbconnectionprovider.h"


DBConnectionProvider::DBConnectionProvider(){}

DBConnectionProvider::~DBConnectionProvider()
{
    closeConnection();
}
bool DBConnectionProvider::createConnection()
{
    QMutexLocker locker(&mutex);
    db = QSqlDatabase::addDatabase ( "QPSQL") ;
    db.setDatabaseName("ejuiqnsm");
    db.setUserName ("ejuiqnsm");
    db.setHostName("balarama.db.elephantsql.com");
    db.setPassword ( "LPxPug_JzXsk_fINkbQCROyGX5Maq3os");
    if (!db.open())
    {
        qDebug() << "Cannot open database:" << db.lastError();
        return false;
    }
    return true;
}



void DBConnectionProvider::closeConnection()
{
    QMutexLocker locker(&mutex);
    db.close();
}

void DBConnectionProvider::createDB()
{
    QMutexLocker locker(&mutex);
    QStringList tables = db.tables();

    if(!tables.contains("users"))
    {
        db.exec("CREATE TABLE users                           \
                (                                             \
                    id SERIAL PRIMARY KEY,                    \
                    name CHARACTER VARYING(30)  NOT NULL,     \
                    password CHARACTER VARYING(30)  NOT NULL  \
                    );");
    }
    if(!tables.contains("games"))
    {
        db.exec("CREATE TABLE games                                       \
                (                                                         \
                    id SERIAL PRIMARY KEY,                                \
                    id_winner INTEGER  NOT NULL REFERENCES users (id),    \
                    id_loser INTEGER  NOT NULL  REFERENCES users (id),    \
                    time_end_game DATE                                    \
                    );");
    }
}

bool DBConnectionProvider::isUserExist(const QString &name)
{
    QMutexLocker locker(&mutex);
    QSqlQuery query = db.exec("select exists(select 1 from users where name='" + name + "');");
    QSqlRecord rec = query.record();
    if(query.next())
    {
        return query.value(rec.indexOf("exists")).toBool();
    }
    return false;
}

bool DBConnectionProvider::isCorrectPassword(const QString &name, const QString &password)
{
    QMutexLocker locker(&mutex);
    QSqlQuery query = db.exec("select exists(select 1 from users where name='" + name + "' and password='" + password + "');");
    QSqlRecord rec = query.record();
    if(query.next())
    {
        return query.value(rec.indexOf("exists")).toBool();
    }
    return false;
}

void DBConnectionProvider::insertUser(const QString &name, const QString &password)
{
    QMutexLocker locker(&mutex);
    db.exec("INSERT INTO users(name, password) VALUES('"+name+"','" + password + "');");
}

