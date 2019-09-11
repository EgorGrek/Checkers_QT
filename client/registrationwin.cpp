#include "registrationwin.h"

RegistrationWin::RegistrationWin(QDialog *parent) : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QLabel* pblName =  new QLabel ("Login: ");
    QLabel* pblPassword =  new QLabel ("Password: ");

    QLineEdit* ptxtName = new QLineEdit;
    QLineEdit* ptxtPassword = new QLineEdit;

    QPushButton* pcmdLogin = new QPushButton("Login");
    QPushButton* pcmdCreateAccount = new QPushButton ("Create account");

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
