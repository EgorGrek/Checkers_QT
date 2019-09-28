#include "registrationwin.h"

RegistrationWin::RegistrationWin(Controller *controller, QDialog *parent) : QDialog(parent)
{
    this->controller = controller;


    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QLabel* pblLogin =  new QLabel ("Login: ");
    QLabel* pblPassword =  new QLabel ("Password: ");

    ptxtLogin = new QLineEdit;
    ptxtPassword = new QLineEdit;

    QPushButton* pcmdLogin = new QPushButton("Login");
    QPushButton* pcmdCreateAccount = new QPushButton ("Create account");

    connect(pcmdLogin, SIGNAL(clicked()),this, SLOT(clickedLoginButton()) );
    connect(pcmdCreateAccount, SIGNAL(clicked()),this, SLOT(clickedCreateAccountButton()) );
    QHBoxLayout* buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(pcmdLogin);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(pcmdCreateAccount);

    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pvbxLayout->addWidget(pblLogin);
    pvbxLayout->addWidget(ptxtLogin);

    pvbxLayout->addWidget(pblPassword);
    pvbxLayout->addWidget(ptxtPassword);

    pvbxLayout->addStretch(1);

    pvbxLayout->addLayout(buttonLayout);


    this->setLayout(pvbxLayout);
}


void RegistrationWin::clickedLoginButton()
{
    controller->logIn(ptxtLogin->text(), ptxtPassword->text());
}

void RegistrationWin::clickedCreateAccountButton()
{
    if(ptxtLogin->text().contains(':'))
    {
        QMessageBox::information(this, "Message", "Sorry, but the login must not contain a symbol ':'");
        return;
    }

    if(ptxtLogin->text().size() < 6 || ptxtPassword->text().size() < 6)
    {
        QMessageBox::information(this, "Message", "Password and login must be longer than 6 characters.");
        return;
    }
    controller->createAccount(ptxtLogin->text(), ptxtPassword->text());
}

void RegistrationWin::cameServerMessage(const qint32& messageType)
{
    if(messageType == OK_LOGIN || messageType == OK_CREATE)
    {
       // this->close();
        this->reject();
    }
    else if(messageType == NOT_LOGIN)
    {
        QMessageBox::information(this, "Message", "Wrong password or login");
    }
    else if(messageType == NOT_CREATE)
    {
        QMessageBox::information(this, "Message", "This login is already taken.\n");
    }
}
