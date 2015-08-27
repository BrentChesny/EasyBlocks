#include "movestepsblock.h"

#include <qmath.h>
#include <QDebug>

#include "../../executionthread.h"
#include "../../intmessage.h"

MoveStepsBlock::~MoveStepsBlock()
{
    if(_steps != NULL)
        delete _steps;
}

QList<Block::ParamType> MoveStepsBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void MoveStepsBlock::executeNextStep(ExecutionThread& executionThread) const
{
    // check if block is valid for execution
    if(_steps == NULL)
        executionThread.endExecution(NULL);

    // get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    // evaluate steps
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_steps);
        m->setValue(1);
        return;
    }

    // move based on the return value
    if(m->getValue() == 1)
    {
        Value* value = (Value*) executionThread.getReturnValue();
        //if no return value -> end execution
        if(value == NULL)
        {
            executionThread.endExecution(NULL);
            return;
        }

        // move sprite
        Sprite* sprite = executionThread.getSprite();
        if(sprite != NULL) {
            int steps = (int)value->toDouble();
            int angle = sprite->getRotation();
            double radians = angle * 0.0174532925;
            QPoint movement = QPoint(steps * qCos(radians), steps * qSin(radians));
            QPoint current = sprite->getPosition();
            sprite->setPosition(current + movement);
        }
        executionThread.endExecution(NULL);
        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool MoveStepsBlock::addParameter(Block* parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR)
        return false;

    _steps = (ExpressionBlock*)parameter;

    return true;
}
