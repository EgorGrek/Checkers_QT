#ifndef REGISTRATIONWIN_H
#define REGISTRATIONWIN_H
#include "controller.h"

#include <QDialog>
#include <QtWidgets>

class RegistrationWin : public QDialog
{
    Q_OBJECT
public:
    explicit RegistrationWin(Controller *controller, QDialog *parent = nullptr);

public slots:
    void login();
    void createAccount();
private:
    Controller *controller;

public:
    QLineEdit* ptxtName;
    QLineEdit* ptxtPassword;
};

#endif // REGISTRATIONWIN_H
