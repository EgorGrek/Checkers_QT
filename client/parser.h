#ifndef PARSER_H
#define PARSER_H

#include <QWidget>

#define UNKNOWN_MESSAGE_TYPE   -1
#define ENEMY_STEP              0
#define START_WHITE             1
#define START_BLACK             2
#define NOT_STEP                3
#define NOT_LOGIN               4
#define NOT_CREATE              5
#define OK_STEP                 6
#define OK_LOGIN                7
#define OK_CREATE               8
#define SHOW_REGISTRATION_WIN   9
#define CONNECTING              10
#define CONNECTED               11

class Parser
{
private:
    Parser();
public:

    static qint32 getMessageType(const QString &str)
    {

        if(str.startsWith("step"))
        {
            return ENEMY_STEP;
        }
        else if(str.startsWith("startwhite"))
        {
            return START_WHITE;
        }
        else if(str.startsWith("startblack"))
        {
            return START_BLACK;
        }
        else if(str.startsWith("notstep"))
        {
            return NOT_STEP;
        }
        else if(str.startsWith("notlogin"))
        {
            return NOT_LOGIN;
        }
        else if(str.startsWith("notcreate"))
        {
            return NOT_CREATE;
        }
        else if(str.startsWith("oklogin"))
        {
            return OK_LOGIN;
        }
        else if(str.startsWith("okcreate"))
        {
            return OK_CREATE;
        }
        else if(str.startsWith("okstep"))
        {
            return OK_STEP;
        }
        else if(str.startsWith("connecting"))
        {
            return CONNECTING;
        }
        else if(str.startsWith("connected"))
        {
            return CONNECTED;
        }
        else if(str.startsWith("showRegistrationWin"))
        {
            return SHOW_REGISTRATION_WIN;
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
};

#endif // PARSER_H
