#include "waitsecondsblock.h"
#include "../../executionthread.h"
#include "../../timemessage.h"


WaitSecondsBlock::~WaitSecondsBlock()
{
    if(_seconds != NULL)
        delete _seconds;
}

QList<Block::ParamType> WaitSecondsBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void WaitSecondsBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_seconds == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //get message
    TimeMessage* m = (TimeMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new TimeMessage();
        executionThread.setMessage(m);
    }

    //evaluate seconds
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_seconds);
        m->setValue(1);
        return;
    }

    //set seconds
    if(m->getValue() == 1)
    {
        Value* value = (Value*) executionThread.getReturnValue();
        //if no return value -> end execution
        if(value == NULL || value->getDataType() != Value::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }
        //set seconds offset
        else {
            m->setMillisecondsOffset((int)(value->toDouble()*1000));
            m->setValue(2);
            return;
        }
    }

    //wait until seconds passed
    if(m->getValue() == 2)
    {
        //if time passed -> end execution
        if(QTime::currentTime() >= m->getTime()) {
            executionThread.endExecution(NULL);
            return;
        }
        //check again
        else
            return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool WaitSecondsBlock::addParameter(Block* parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR)
        return false;

    _seconds = (ExpressionBlock*)parameter;

    return true;
}
