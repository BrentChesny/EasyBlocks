#include "resizetoblock.h"

#include "../../executionthread.h"
#include "../../valuemessage.h"

ResizeToBlock::~ResizeToBlock()
{
    if (_xSize != NULL)
        delete _xSize;

    if (_ySize != NULL)
        delete _ySize;
}

QList<Block::ParamType> ResizeToBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void ResizeToBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_xSize == NULL || _ySize == NULL)
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
        executionThread.setNextBlock(_xSize);
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
        executionThread.setNextBlock(_ySize);
        m->setNumber(2);
        return;
    }

    //Change size to given size
    if(m->getNumber() == 2)
    {
        Value* v = executionThread.getReturnValue();
        //check right value
        if(v == NULL || v->getDataType() != Value::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }

        //Change size
        Sprite* sprite = executionThread.getSprite();
        if(sprite != NULL) {
            int x = (int) m->getValue()->toDouble();
            int y = (int) v->toDouble();
            sprite->setSize(QSize(x, y));
        }
        executionThread.endExecution(NULL);
        return;
    }

    executionThread.endExecution(NULL);
}

bool ResizeToBlock::addParameter(Block* parameter, int index)
{
    if(index < 0 || index > 1 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR)
        return false;

    if (index == 0)
        _xSize = (ExpressionBlock*)parameter;
    else if (index == 1)
        _ySize = (ExpressionBlock*)parameter;

    return true;
}
