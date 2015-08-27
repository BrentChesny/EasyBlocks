#include "ifblock.h"
#include "../../executionthread.h"
#include "../../intmessage.h"

IfBlock::~IfBlock()
{
    if(_condition != NULL)
        delete _condition;
    if(_body != NULL)
        delete _body;
}

QList<Block::ParamType> IfBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::BOOLEAN_EXPRESSION);
    return params;
}

void IfBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_condition == NULL || _body == NULL) {
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
        //if no return value or false -> end execution
        if(value == NULL || !value->toBool())
        {
            executionThread.endExecution(NULL);
            return;
        }

        //if condition true -> execute body
        executionThread.setNextBlock(_body);
        m->setValue(2);
        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool IfBlock::addParameter(Block* parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::BOOLEAN_EXPRESSION && parameter->getReturnType() != Block::BOOLEAN_VAR)
        return false;

    _condition = (ExpressionBlock*)parameter;

    return true;
}

bool IfBlock::addBody(StatementBlock* body, int index)
{
    if(index != 0 || body == NULL)
        return false;

    _body = body;

    return true;
}
