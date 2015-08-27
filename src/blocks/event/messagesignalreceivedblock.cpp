#include "messagesignalreceivedblock.h"

#include "../../executionhandler.h"
#include "../../statementblock.h"
#include "../../programmodel.h"
#include "../../intmessage.h"

#include <QDebug>

MessageSignalReceivedBlock::~MessageSignalReceivedBlock()
{
    if(_message != NULL)
        delete _message;

    delete _signalQueue;
}

QList<Block::ParamType> MessageSignalReceivedBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::STRING_EXPRESSION);
    return params;
}

void MessageSignalReceivedBlock::sendSignal(const Signal& signal, Sprite* sprite)
{
    //check pointer and type of signal
    if(sprite == NULL || signal.getType() != Signal::MESSAGE)
        return;

    //add signal to queue
    _signalQueue->enqueue(signal);

    //run statements
    sprite->getProgramModel()->getExecutionHandler()->addExecutionThread(this, sprite->getVarTable(), sprite);
}

void MessageSignalReceivedBlock::executeNextStep(ExecutionThread &executionThread) const
{
    //check if block is valid for execution
    if(_message == NULL) {
        //take signal from queue
        if(_signalQueue->size() > 0)
            _signalQueue->dequeue();
        executionThread.endExecution(NULL);
        return;
    }

    //get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    //evaluate message
    if(m->getValue() == 0) {
        executionThread.setNextBlock(_message);
        m->setValue(1);
        return;
    }

    if(m->getValue() == 1) {


        Value* message = executionThread.getReturnValue();
        if(message == NULL || message->getDataType() != Value::STRING) {
            //take signal from queue
            if(_signalQueue->size() > 0)
                _signalQueue->dequeue();
            executionThread.endExecution(NULL);
            return;
        }
        //if no signal, end execution
        if(_signalQueue->isEmpty()) {
            executionThread.endExecution(NULL);
            return;
        }
        //if message does not equal the signal message, end execution
        if(message->toString() != _signalQueue->dequeue().getMessage()) {
            executionThread.endExecution(NULL);
            return;
        }

        //message equals the signal message -> start execution
        executionThread.setNextBlock(getStatement());
        m->setValue(2);
        return;
    }

    executionThread.endExecution(NULL);

}

bool MessageSignalReceivedBlock::addParameter(Block *parameter, int index)
{
    if(parameter == NULL || index != 0)
        return false;

    if(parameter->getReturnType() == Block::STRING_EXPRESSION || parameter->getReturnType() == Block::STRING_VAR) {
        _message = (ExpressionBlock*)parameter;
        return true;
    }

    return false;
}
