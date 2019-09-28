#include "controller.h"
#include "parser.h"
#include <QtWidgets>

Controller::Controller(QWidget *parent) : QObject (parent)
{
    gameType = gameNotStart;
    model = new Model;
    serverhandler = new ServerHandler();
    connect(serverhandler, SIGNAL(serverError(const QString&)), SIGNAL(serverError(const QString&)));
    connect(serverhandler, SIGNAL(messageCame(const QString&)), SLOT(processingMessage(const QString&)));
}

void Controller::actionPlay_on_one_computer()
{
    gameType = onOneComputer;
    model->startNewGame();
    userColor = model->getWhoseMove();
    signalWhoseMove();
    emit fieldChanged();
}

void Controller::startPlayAgainstOpponentOnServer()
{
    gameType = againstOpponentOnServer;
    model->startNewGame();
    signalWhoseMove();
    emit fieldChanged();
}

void Controller::actionSearch_for_an_opponent()
{
    if(serverhandler->isUserAuthorized())
    {
        serverhandler->searchForAnOpponent();
        emit haveInfo("Searching for an opponent...");
    }
    else
    {
        emit cameMessage("You must be logged in to use this function :)");
    }
}

void Controller::clickedLogIn_OutButton()
{
    if(serverhandler->isHaveConnectionToServer())
    {
        if(serverhandler->isUserAuthorized())
        {
            //TODO make log out
        }
        else
        {
            emit cameServerMessage(SHOW_REGISTRATION_WIN);
        }
    }
    else
    {
        serverhandler->connectToServer();
    }
}

void Controller::actionPlay_against_bot()
{
    emit cameMessage("This function is not available yet, sorry :(");
}

QVector<QVector<qint8>> Controller::getField()
{
    return model->getField();
}

QString Controller::getLoser()
{
    return model->getLoser();
}

qint8 Controller::getWhoseMove()
{
    return model->getWhoseMove();
}

bool Controller::mousePressed(QPoint from)
{
    mousePressCoordinates = from;
    if(userColor == model->getCellColor(from))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Controller::mouseReleased(QPoint to)
{
    if(gameType == onOneComputer)
    {
        model->makeMove(mousePressCoordinates, to);
        userColor = model->getWhoseMove();
    }
    else if(gameType == againstOpponentOnServer)
    {
        if(model->getWhoseMove() == userColor)
        {
            if(model->makeMove(mousePressCoordinates, to))
            {
                serverhandler->makeMove(mousePressCoordinates, to);
            }
        }
    }
    signalWhoseMove();
    emit fieldChanged();
    return;
}

void Controller::signalWhoseMove()
{
    if(model->getWhoseMove() != NOBODY)
    {
        QString whoseMove = model->getWhoseMove() == WHITEPLAYER ? "White" : "Black";
        emit haveInfo("Move:" + whoseMove);
    }
    else
    {
        emit haveInfo("");
    }
}

void Controller::connectToServer()
{
    serverhandler->connectToServer();
}

Controller::~Controller()
{
    delete model;

    delete serverhandler;
}

void Controller::logIn(QString userName, QString userPassword)
{
    serverhandler->logIn(userName, userPassword);
}

void Controller::createAccount(QString userName, QString userPassword)
{
    serverhandler->createAccount(userName, userPassword);
}

void Controller::processingMessage(const QString& message)
{
    qint32 messageType = Parser::getMessageType(message);
    qDebug() << message;
    if(messageType == UNKNOWN_MESSAGE_TYPE)
    {
        emit serverError("Error: We don't understand request from server :(,\n maybe you should update application");
    }
    else if(messageType == ENEMY_STEP)
    {
        QPair<QPoint, QPoint> from_to_move = Parser::parsStep(message);
        model->makeMove(from_to_move.first, from_to_move.second);
        signalWhoseMove();
        emit fieldChanged();
    }
    else if(messageType == OK_LOGIN || messageType == OK_CREATE)
    {
        emit userAuthorized(serverhandler->getUserLogin());

    }
    else if(messageType == CONNECTED)
    {
        emit haveInfo("Connection to the server was successful");
    }
    else if(messageType == OPPONENT_FOUND)
    {
        emit cameMessage("Opponent found - " + Parser::parseOpponent(message));
        serverhandler->acceptOpponent();
    }
    else if(messageType == START_WHITE)
    {
        emit cameMessage("You plaing - WHITE");
        userColor = WHITEPLAYER;
        startPlayAgainstOpponentOnServer();
    }
    else if(messageType == START_BLACK)
    {
        emit cameMessage("You plaing - BLACK");
        userColor = BLACKPLAYER;
        startPlayAgainstOpponentOnServer();
    }
    emit cameServerMessage(messageType);
}

