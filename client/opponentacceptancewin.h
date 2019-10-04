#ifndef OPPONENTACCEPTANCEWIN_H
#define OPPONENTACCEPTANCEWIN_H

#include "controller.h"

#include <QDialog>
#include <QtWidgets>

class OpponentAcceptanceWin : public QDialog
{
    Q_OBJECT
public:
    explicit OpponentAcceptanceWin(Controller *controller, QString opponentName,  QDialog *parent = nullptr);

public slots:
    void clickedAcceptButton();
    void clickedDenialButton();
    void cameServerMessage(const qint32&);


private:
    Controller *controller;
};

#endif // OPPONENTACCEPTANCEWIN_H
