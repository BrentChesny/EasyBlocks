#include "waituntilblock.h"
#include "../../executionthread.h"
#include "../../intmessage.h"

WaitUntilBlock::~WaitUntilBlock()
{
    if(_condition != NULL)
        delete _condition;
}

QList<Block::ParamType> WaitUntilBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::BOOLEAN_EXPRESSION);
    return params;
}

void WaitUntilBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_condition == NULL) {
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

    //test condition
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_condition);
        m->setValue(1);
        return;
    }

    //check condition and run body if condition evaluated true
    if(m->getValue() == 1)
    {
        Value* value = (Value*) executionThread.getReturnValue();
        //if no return value or true -> end execution of this block to continue execution in the blocksequence
        if(value == NULL || value->toBool())
        {
            executionThread.endExecution(NULL);
            return;
        }
        //if condition is false, check condition again
        else {
            m->setValue(0);
            return;
        }
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool WaitUntilBlock::addParameter(Block* parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::BOOLEAN_EXPRESSION && parameter->getReturnType() != Block::BOOLEAN_VAR)
        return false;

    _condition = (ExpressionBlock*)parameter;

    return true;
}
