#include "repeatxblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"

RepeatXBlock::~RepeatXBlock()
{
    if(_num != NULL)
        delete _num;
    if(_body != NULL)
        delete _body;
}

QList<Block::ParamType> RepeatXBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void RepeatXBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_num == NULL || _body == NULL)
        executionThread.endExecution(NULL);

    //get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(-2);
        executionThread.setMessage(m);
    }

    // evaluate how many times the loop has to run
    if(m->getValue() == -2)
    {
        executionThread.setNextBlock(_num);
        m->setValue(-1);
        return;
    }

    // loop has run x times
    if (m->getValue() == -1)
    {
        Value* value = (Value*) executionThread.getReturnValue();
        //if no return value or false -> end execution
        if(value == NULL)
        {
            executionThread.endExecution(NULL);
            return;
        }
        m->setValue((int) value->toDouble());
    }

    // loop has run x times
    if (m->getValue() == 0)
    {
        executionThread.endExecution(NULL);
        return;
    }

    // run body
    if(m->getValue() > 0)
    {
        executionThread.setNextBlock(_body);
        m->setValue(m->getValue() - 1);
        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool RepeatXBlock::addParameter(Block* parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR)
        return false;

    _num = (ExpressionBlock*)parameter;

    return true;
}

bool RepeatXBlock::addBody(StatementBlock* body, int index)
{
    if(index != 0 || body == NULL)
        return false;

    _body = body;

    return true;
}
