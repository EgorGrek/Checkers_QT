#include "opponentacceptancewin.h"

OpponentAcceptanceWin::OpponentAcceptanceWin(Controller *controller,
                                             QString opponentName,  QDialog *parent) : QDialog(parent)
{
    this->controller = controller;

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QLabel* pblMessage =  new QLabel ("Will you play against - " + opponentName + " ?");

    QPushButton* pcmdAccept= new QPushButton("Accept");
    QPushButton* pcmdDenial = new QPushButton ("Denial");

    connect(pcmdAccept, SIGNAL(clicked()),this, SLOT(clickedAcceptButton()));
    connect(pcmdDenial, SIGNAL(clicked()),this, SLOT(clickedDenialButton()));

    QHBoxLayout* buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(pcmdAccept);
    buttonLayout->addStretch(1);
    buttonLayout->addWidget(pcmdDenial);

    QVBoxLayout* pvbxLayout = new QVBoxLayout;

    pvbxLayout->addWidget(pblMessage);
    pvbxLayout->addStretch(1);
    pvbxLayout->addLayout(buttonLayout);


    this->setLayout(pvbxLayout);
}

void OpponentAcceptanceWin::clickedAcceptButton()
{
    controller->acceptOpponent();
    this->reject();
}

void OpponentAcceptanceWin::clickedDenialButton()
{
    controller->denialOpponent();
    this->reject();
}

void OpponentAcceptanceWin::cameServerMessage(const qint32&)
{
   //TODO if opponent denial you - close this win.
}
