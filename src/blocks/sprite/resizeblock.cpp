#include "resizeblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"

ResizeBlock::~ResizeBlock()
{
    if(_increase != NULL)
        delete _increase;
}

QList<Block::ParamType> ResizeBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void ResizeBlock::executeNextStep(ExecutionThread& executionThread) const
{
    // check if block is valid for execution
    if(_increase == NULL)
        executionThread.endExecution(NULL);

    // get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    // evaluate increase
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_increase);
        m->setValue(1);
        return;
    }

    // resize based on the return value
    if(m->getValue() == 1)
    {
        Value* value = (Value*) executionThread.getReturnValue();
        //if no return value -> end execution
        if(value == NULL || value->getDataType() != Value::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }

        // resize sprite
        Sprite* sprite = executionThread.getSprite();
        if(sprite != NULL) {
            int increase = (int)value->toDouble();
            QSize size = sprite->getSize();
            size.scale(size.width()+increase, size.height()+increase, Qt::IgnoreAspectRatio);
            sprite->setSize(size);
        }
        executionThread.endExecution(NULL);
        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool ResizeBlock::addParameter(Block* parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR)
        return false;

    _increase = (ExpressionBlock*)parameter;

    return true;
}
