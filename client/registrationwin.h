#ifndef REGISTRATIONWIN_H
#define REGISTRATIONWIN_H

#include "controller.h"
#include "parser.h"

#include <QDialog>
#include <QtWidgets>

class RegistrationWin : public QDialog
{
    Q_OBJECT
public:
    explicit RegistrationWin(Controller *controller, QDialog *parent = nullptr);

public slots:
    void clickedLoginButton();
    void clickedCreateAccountButton();
    void cameServerMessage(const qint32&);



private:
    Controller *controller;
    QLineEdit* ptxtLogin;
    QLineEdit* ptxtPassword;

};

#endif // REGISTRATIONWIN_H
