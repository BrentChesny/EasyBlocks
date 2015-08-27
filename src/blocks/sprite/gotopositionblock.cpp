#include "gotopositionblock.h"

#include <QDebug>

#include "../../executionthread.h"
#include "../../valuemessage.h"

GoToPositionBlock::~GoToPositionBlock()
{
    if (_xPos != NULL)
        delete _xPos;

    if (_yPos != NULL)
        delete _yPos;
}

QList<Block::ParamType> GoToPositionBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void GoToPositionBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_xPos == NULL || _yPos == NULL)
        executionThread.endExecution(NULL);

    //get message
    ValueMessage* m = (ValueMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new ValueMessage();
        executionThread.setMessage(m);
    }

    //evaluate left
    if(m->getNumber() == 0)
    {
        executionThread.setNextBlock(_xPos);
        m->setNumber(1);
        return;
    }

    //evaluate right
    if(m->getNumber() == 1)
    {
        //take copy of returnValue
        m->setValue(executionThread.getReturnValue()->copy());
        //check left value
        if(m->getValue() == NULL || m->getValue()->getDataType() != Value::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }
        executionThread.setNextBlock(_yPos);
        m->setNumber(2);
        return;
    }

    //move sprite to position
    if(m->getNumber() == 2)
    {
        Value* v = executionThread.getReturnValue();
        //check right value
        if(v == NULL || v->getDataType() != Value::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }

        // move sprite
        Sprite* sprite = executionThread.getSprite();
        if(sprite != NULL) {
            int x = (int) m->getValue()->toDouble();
            int y = (int) v->toDouble();
            sprite->setPosition(QPoint(x, y));
        }
        executionThread.endExecution(NULL);
        return;
    }

    executionThread.endExecution(NULL);
}

bool GoToPositionBlock::addParameter(Block* parameter, int index)
{
    if(index < 0 || index > 1 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR)
        return false;

    if (index == 0)
        _xPos = (ExpressionBlock*)parameter;
    else if (index == 1)
        _yPos = (ExpressionBlock*)parameter;

    return true;
}
