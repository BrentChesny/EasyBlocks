#include "executionhandler.h"
#include <QDebug>

ExecutionHandler::ExecutionHandler(IOHandler *ioHandler) : _ioHandler(ioHandler)
{
    _running = false;
    _working = false;
    _qtimer = new QTimer();
    _qtimer->setInterval(1);

    connect(_qtimer, SIGNAL(timeout()), this, SLOT(executionTick()));
}

ExecutionHandler::~ExecutionHandler()
{
    while(!_threads.isEmpty()) {
        delete _threads.first();
        _threads.removeFirst();
    }

    delete _qtimer;
}

void ExecutionHandler::start()
{
    _prevDrawTime = QDateTime::currentDateTime();
    _prevExecutionTime = QDateTime::currentDateTime();
    _running = true;

    _qtimer->start();
}

void ExecutionHandler::stop()
{
    _running = false;
    _qtimer->stop();
}

int ExecutionHandler::getNumThreads() const
{
    return _threads.size();
}

void ExecutionHandler::addExecutionThread(Block* block, VarTable* varTable, Sprite* sprite)
{
    if(block == NULL || varTable == NULL || sprite == NULL)
        return;

    ExecutionThread* thread = new ExecutionThread(block, varTable, sprite, _ioHandler);

    _threads.append(thread);
}

void ExecutionHandler::executionTick()
{
    if(!_running)
        return;

    if(_working)
    {
        qDebug() << "can't keep up: skipping tick";
        return;
    }

    _working = true;

    //QDateTime currentTime = QDateTime::currentDateTime();

    if(EXECUTION_TICK_INTERVAL <= _prevExecutionTime.msecsTo(QDateTime::currentDateTime()))
    {
        executeThreads();
        emit executionTicked();
        _prevExecutionTime = _prevExecutionTime.addMSecs(EXECUTION_TICK_INTERVAL);
    }

    if(DRAW_TICK_INTERVAL <= _prevDrawTime.msecsTo(QDateTime::currentDateTime()))
    {
        emit drawingTicked();
        _prevDrawTime = _prevDrawTime.addMSecs(DRAW_TICK_INTERVAL);
    }

    _working = false;
}

void ExecutionHandler::executeThreads()
{
    if(_threads.size() == 0)
        return;

    for(int i = _threads.size()-1; i >= 0; i--) {
        ExecutionThread* et = _threads.at(i);
        et->executeNext();

        if(et->isEmpty()) {
            delete et;
            _threads.removeAt(i);
        }
    }
}
