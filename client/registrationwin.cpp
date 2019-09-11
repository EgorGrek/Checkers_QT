#include "registrationwin.h"

RegistrationWin::RegistrationWin(Controller *controller, QDialog *parent) : QDialog(parent)
{
    this->controller = controller;


    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QLabel* pblName =  new QLabel ("Login: ");
    QLabel* pblPassword =  new QLabel ("Password: ");

    ptxtName = new QLineEdit;
    ptxtPassword = new QLineEdit;

    QPushButton* pcmdLogin = new QPushButton("Login");
    QPushButton* pcmdCreateAccount = new QPushButton ("Create account");

    connect(pcmdLogin, SIGNAL(clicked()),this, SLOT(login()) );
    connect(pcmdCreateAccount, SIGNAL(clicked()),this, SLOT(createAccount()) );
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(pcmdLogin);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(pcmdCreateAccount);

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(pblName);
    pvbxLayout->addWidget(ptxtName);

    pvbxLayout->addWidget(pblPassword);
    pvbxLayout->addWidget(ptxtPassword);

    pvbxLayout->addStretch(1);

    pvbxLayout->addLayout(buttonLayout);


    this->setLayout(pvbxLayout);
}


void RegistrationWin::login()
{
    controller->logIn(ptxtName->text(), ptxtPassword->text());
}
void RegistrationWin::createAccount()
{
    controller->createAccount(ptxtName->text(), ptxtPassword->text());
}
