#include "rotatespriteblock.h"

#include <QDebug>

#include "../../executionthread.h"
#include "../../intmessage.h"

RotateSpriteBlock::~RotateSpriteBlock()
{
    if(_rotationValue != NULL)
        delete _rotationValue;
}

QList<Block::ParamType> RotateSpriteBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void RotateSpriteBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_rotationValue == NULL)
        executionThread.endExecution(NULL);

    //get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    //evaluate rotationValue
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_rotationValue);
        m->setValue(1);
        return;
    }

    //rotate based on the returned value
    if(m->getValue() == 1)
    {
        Value* value = (Value*) executionThread.getReturnValue();
        //if no return value -> end execution
        if(value == NULL)
        {
            executionThread.endExecution(NULL);
            return;
        }

        //rotate sprite
        Sprite* sprite = executionThread.getSprite();
        if(sprite != NULL) {
            int rotation = (int)value->toDouble();
            rotation += sprite->getRotation();
            sprite->setRotation(rotation%360);
        }
        executionThread.endExecution(NULL);
        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool RotateSpriteBlock::addParameter(Block* parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR)
        return false;

    _rotationValue = (ExpressionBlock*)parameter;

    return true;
}
