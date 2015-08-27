#include <QtAlgorithms>
#include <QDebug>

#include "programmodel.h"


ProgramModel::ProgramModel()
{
    _ioHandler = new IOHandler();
    _executionHandler = new ExecutionHandler(_ioHandler);
    _screen = new Screen;
    _globalVars = new SimpleVarTable;

    connect(_executionHandler, SIGNAL(drawingTicked()), this, SLOT(tickReceived()));

    _working = false;
}

ProgramModel::~ProgramModel()
{
    delete _executionHandler;
    delete _ioHandler;
    delete _screen;
    delete _globalVars;

    qDeleteAll(_sprites);
    qDeleteAll(_userStatements);
}


void ProgramModel::sendSignal(const Signal &signal)
{
    foreach (Sprite* sprite, _sprites) {
        sprite->sendSignal(signal);
    }
}

Sprite* ProgramModel::createSprite(QPixmap* image)
{
    Sprite* sprite = new Sprite(_globalVars, image, this);

    _sprites.append(sprite);

    return sprite;
}

void ProgramModel::addUserStatement(UserStatement *userStatement)
{
    if(userStatement == NULL)
        return;

    _userStatements.append(userStatement);
}

void ProgramModel::tickReceived()
{
    //qDebug() << "tick received";

    if(_working) {
        qDebug() << "Programmodel: can't keep up\n";
        return;
    }
    _working = true;
    emit update();
    _working = false;
}
