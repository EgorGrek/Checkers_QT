#include "checkersclientwin.h"
#include "ui_checkersclientwin.h"
#include "viewcheckers.h"
#include "checker.h"
#include "checkerqueen.h"
#include "registrationwin.h"

#include <QPainter>
#include <QApplication>
#include <QtWidgets>
#include <QtGlobal>

#define BOARDSIZE 8

CheckersClientWin::CheckersClientWin(QSize winSize, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CheckersClientWin)
{
    ui->setupUi(this);

    connect(ui->actionRules, SIGNAL(triggered()), this, SLOT(showRules()));

    controller = new Controller();
    connect(ui->actionPlay_on_one_computer, SIGNAL(triggered()), controller, SLOT(actionPlay_on_one_computer()));
    connect(ui->actionPlay_against_bot, SIGNAL(triggered()), controller, SLOT(actionPlay_against_bot()));
    connect(ui->actionSearch_for_an_opponent, SIGNAL(triggered()), controller, SLOT(actionSearch_for_an_opponent()));


    connect(controller, SIGNAL(fieldChanged()), this, SLOT(redraw()));
    connect(controller, SIGNAL(serverError(const QString&)), this, SLOT(serverError(const QString&)));
    connect(controller, SIGNAL(cameMessage(const QString&)), this, SLOT(showMessage(const QString&)));
    connect(controller, SIGNAL(haveInfo(const QString&)), this, SLOT(showInfo(const QString&)));
    connect(controller, SIGNAL(userAuthorized(const QString&)), this, SLOT(showUserLogin(const QString&)));
    connect(controller, SIGNAL(cameServerMessage(const qint32&)), this, SLOT(cameServerMessage(const qint32&)));

    this->setWindowTitle("Checkers");
    this->setWindowIcon(QIcon(":/images/icon_win_client.png"));

    this->move(winSize.width() / 4, winSize.height() / 4); // put in the center of the display
    this->setWindowFlags(Qt::Widget);


    QWidget *pCentralWidget = new QWidget;


    pView = new ViewCheckers(new QGraphicsScene());

    QHBoxLayout* phbxLayout = new QHBoxLayout;
    QHBoxLayout* userInfoLayout = new QHBoxLayout;
    QVBoxLayout* pvbxLayout = new QVBoxLayout;
    pcmdLogIn_Out = new QPushButton("Log in");

    phbxLayout->addWidget(pcmdLogIn_Out);
    phbxLayout->addStretch();

    userInfo = new QLabel("");
    userLogin = new QLabel("");
    userInfoLayout->addWidget(userInfo);
    phbxLayout->addStretch();
    userInfoLayout->addWidget(userLogin);

    pvbxLayout->addLayout(phbxLayout);
    pvbxLayout->addLayout(userInfoLayout);
    pvbxLayout->addWidget(pView);

    pCentralWidget->setLayout(pvbxLayout);

    this->setCentralWidget(pCentralWidget);

    connect(pcmdLogIn_Out, SIGNAL(clicked()), controller, SLOT(clickedLogIn_OutButton()));

    qint32 minSideWin = qMin(winSize.width(), winSize.height());      // square win
    this->setFocus();
    this->show();
    this->resize(minSideWin / 2, minSideWin / 2);  // because the show method resizes widgets
                                                    // and if do it before show()
                                                    // the field twitches when resizing the window
}

CheckersClientWin::~CheckersClientWin()
{
    delete pView;
    delete controller;
    delete ui;
}

void CheckersClientWin::drawField()
{
    QGraphicsScene *scene = pView->scene();

    qint32 minSideView = qMin(pView->width(), pView->height());           //
    scene->setSceneRect(QRectF(0, 0, minSideView / 2, minSideView / 2)); // square field

    QRectF rect = scene->sceneRect();

    qreal *xp1 = new qreal, *yp1 = new qreal, *xp2 = new qreal, *yp2 = new qreal;
    rect.getCoords(xp1, yp1, xp2, yp2);

     qreal stepX = *xp2 / BOARDSIZE;
     qreal stepY = *yp2 / BOARDSIZE;

     bool whiteOrBlack = false;
     for(qreal yp = *yp1; yp < *yp2; yp += stepY)
     {
         for(qreal xp = *xp1; xp < *xp2; xp += stepX)
         {
            if(whiteOrBlack)
            {
                scene->addRect(QRectF(QPointF(xp, yp),
                                      QPointF(xp + stepX, yp + stepY)),
                               QPen(Qt::black, 2),
                               QBrush(Qt::black) );

            }
            else
            {
              scene->addRect(QRectF(QPointF(xp, yp),
                                      QPointF(xp + stepX, yp + stepY)),
                               QPen(Qt::black, 2),
                               QBrush(Qt::white));
            }
             whiteOrBlack = !whiteOrBlack;

         }
         whiteOrBlack = !whiteOrBlack;
     }
     delete xp1;
     delete yp1;
     delete xp2;
     delete yp2;
}

void CheckersClientWin::drawCheckers()
{
    QGraphicsScene *scene = pView->scene();
    QVector<QVector<qint8>> field = controller->getField();
    QRectF rect = scene->sceneRect();

    qreal *xp1 = new qreal, *yp1 = new qreal, *xp2 = new qreal, *yp2 = new qreal;
    rect.getCoords(xp1, yp1, xp2, yp2);

    qreal stepX = *xp2 / BOARDSIZE;
    qreal stepY = *yp2 / BOARDSIZE;
    qint8 indexI = 0;
    qint8 indexJ = 0;
    for(const QVector<qint8> &i : field)
    {
        for(const qint8 &j : i)
        {
            if(j == WHITEUNIT)
            {
                Checker* pChecker = new Checker(this);
                scene->addItem(pChecker);

                // -3 and +3 - due to the error in dividing the field length
                pChecker->setRect(QRectF(QPointF(indexJ * stepX + 3, indexI * stepY + 3),
                                         QPointF((indexJ + 1) * stepX - 3, (indexI + 1) * stepY - 3)));
                pChecker->setPen(QPen(Qt::black, stepX / 20));
                pChecker->setBrush(QBrush(Qt::white));

            }
            else if(j == BLACKUNIT)
            {
                Checker* pChecker = new Checker(this);
                scene->addItem(pChecker);

                pChecker->setRect(QRectF(QPointF(indexJ * stepX + 3, indexI * stepY + 3),
                                         QPointF((indexJ + 1) * stepX - 3, (indexI + 1) * stepY - 3)));
                pChecker->setPen(QPen(Qt::white, stepX / 20));
                pChecker->setBrush(QBrush(Qt::black));

            }
            else if(j == WHITEQUEEN)
            {
                QGraphicsEllipseItem* pChecker = new QGraphicsEllipseItem;
                QGraphicsLineItem *queenLine = new QGraphicsLineItem;

                queenLine->setLine(indexJ * stepX + 3, indexI * stepY + 3,
                                (indexJ + 1) * stepX - 3, (indexI + 1) * stepY - 3);
                queenLine->setPen(QPen(Qt::black, 4));

                pChecker->setRect(QRectF(QPointF(indexJ * stepX + 3, indexI * stepY + 3),
                                         QPointF((indexJ + 1) * stepX - 3, (indexI + 1) * stepY - 3)));
                pChecker->setPen(QPen(Qt::black, stepX / 20));
                pChecker->setBrush(QBrush(Qt::white));

                CheckerQueen *group = new CheckerQueen(this);
                group->addToGroup(pChecker);
                group->addToGroup(queenLine);

                scene->addItem(group);

            }
            else if(j == BLACKQUEEN)
            {
                Checker* pChecker = new Checker(this);
                QGraphicsLineItem *queenLine = new QGraphicsLineItem;

                queenLine->setLine(indexJ * stepX + 3, indexI * stepY + 3,
                                   (indexJ + 1) * stepX - 3, (indexI + 1) * stepY - 3);
                queenLine->setPen(QPen(Qt::white, stepX / 20));

                pChecker->setRect(QRectF(QPointF(indexJ * stepX + 3, indexI * stepY + 3),
                                         QPointF((indexJ + 1) * stepX - 3, (indexI + 1) * stepY - 3)));
                pChecker->setPen(QPen(Qt::white, stepX / 20));
                pChecker->setBrush(QBrush(Qt::black));

                CheckerQueen *group = new CheckerQueen(this);
                group->addToGroup(pChecker);
                group->addToGroup(queenLine);

                scene->addItem(group);
            }

            indexJ += 1;
        }
        indexJ = 0;
        indexI += 1;
    }
}

void CheckersClientWin::redraw()
{
    pView->scene()->clear();
    drawField();
    drawCheckers();
    showLoser();
}

bool CheckersClientWin::mausePressed(QPointF mouseCoordinates)
{
    return controller->mousePressed(getFieldPosition(mouseCoordinates));
}

void CheckersClientWin::mauseReleased(QPointF mouseCoordinates)
{
    controller->mouseReleased(getFieldPosition(mouseCoordinates));
}

QPoint CheckersClientWin::getFieldPosition(QPointF mouseCoordinates)
{

    QPoint fieldPosition;
    fieldPosition.rx() = qint32(mouseCoordinates.x() / (pView->scene()->width() / 8));
    fieldPosition.ry() = qint32(mouseCoordinates.y()/ (pView->scene()->height() / 8));
    return fieldPosition;
}

void CheckersClientWin::resizeEvent(QResizeEvent *event)
{
    resize(event->size().width(), event->size().height());
    pView->scene()->clear();
    drawField();
    drawCheckers();
}

void CheckersClientWin::showLoser()
{
    QString loser = controller->getLoser();
    if(loser != "")
    {
        QMessageBox::information(this, "Message", loser + " LOSE!!!");
    }
}

void CheckersClientWin::showRules()
{
    QMessageBox::information(this, "Rules", "Just use google search.");

}

void CheckersClientWin::serverError(const QString &err)
{
    QMessageBox::information(this, "Error", err);
}

void CheckersClientWin::showMessage(const QString &message)
{
    QMessageBox::information(this, "Message", message);
}

void CheckersClientWin::showInfo(const QString &info)
{
    userInfo->setText(info);
}

void CheckersClientWin::showUserLogin(const QString &login)
{
    userLogin->setText(login);
    pcmdLogIn_Out->setText("Log out");
}

void CheckersClientWin::cameServerMessage(const qint32& message)
{
    if(message == SHOW_REGISTRATION_WIN)
    {
        RegistrationWin *registrationWin = new RegistrationWin(controller);

        connect(controller, SIGNAL(cameServerMessage(const qint32&)), registrationWin, SLOT(cameServerMessage(const qint32&)));

        registrationWin->setModal(true);
        registrationWin->show();
    }
    else if(message == START_WHITE)
    {
        QMessageBox::information(this, "Message", "We found opponent for you, you are playing white.");
    }
    else if(message == START_BLACK)
    {
        QMessageBox::information(this, "Message", "We found opponent for you, you are playing black.");
    }
}

