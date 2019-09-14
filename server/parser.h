#ifndef PARSER_H
#define PARSER_H

#include <QWidget>

class Parser
{
public:
    Parser();
    QPair<QPoint, QPoint> parsStep(const QString &str);
};

#endif // PARSER_H
