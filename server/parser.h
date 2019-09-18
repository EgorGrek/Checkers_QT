#ifndef PARSER_H
#define PARSER_H

#include <QWidget>

#define LOGIN_LENGTH_MIN        6
#define LOGIN_LENGTH_MAX        30

#define CLIENT_STEP             0
#define CLIENT_LOGIN            1
#define CLIENT_CREATE           2
#define UNKNOWN_MESSAGE_TYPE   -1
class Parser
{
private:
    Parser();
public:

    static qint32 getMessageType(const QString &str)
    {
        if(str.startsWith("step:"))
        {
            return CLIENT_STEP;
        }
        else if(str.startsWith("login:"))
        {
            return CLIENT_LOGIN;
        }
        else if(str.startsWith("create:"))
        {
            return CLIENT_CREATE;
        }

        return UNKNOWN_MESSAGE_TYPE;
    }

    static QPair<QPoint, QPoint> parsStep(const QString &str)
    {
        QRegExp rx( "step:([0-7]):([0-7]):([0-7]):([0-7])" );
        if( rx.indexIn(str) == -1 )
            return QPair<QPoint, QPoint>(QPoint(), QPoint());
        return QPair<QPoint, QPoint>(QPoint(rx.cap(1).toInt(), rx.cap(2).toInt()),
                                     QPoint(rx.cap(3).toInt(), rx.cap(4).toInt()));
    }

    static QPair<QString, QString> parsLogin(const QString &str)
    {
        QRegExp rx(
                    QString("login:((\\w|\\d){%1,%2}):(\\w|\\d)")
                    .arg(LOGIN_LENGTH_MIN)
                    .arg(LOGIN_LENGTH_MAX)
                    );
        if( rx.indexIn(str) == -1 )
            return QPair<QString, QString>(QString(), QString());
        return QPair<QString, QString>(QString(rx.cap(1)),
                                       QString(rx.cap(2)));
    }

    static QPair<QString, QString> parsCreateAcc(const QString &str)
    {
        QRegExp rx(
                    QString("create:((\\w|\\d){%1,%2}):(\\w+|\\d+)")
                    .arg(LOGIN_LENGTH_MIN)
                    .arg(LOGIN_LENGTH_MAX)
                    );
        if( rx.indexIn(str) == -1 )
            return QPair<QString, QString>(QString(), QString());

        return QPair<QString, QString>(QString(rx.cap(1)),
                                       QString(rx.cap(3)));
    }
};

#endif // PARSER_H
