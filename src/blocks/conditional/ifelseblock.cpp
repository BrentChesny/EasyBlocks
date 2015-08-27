#include "ifelseblock.h"
#include "../../executionthread.h"
#include "../../intmessage.h"

IfElseBlock::~IfElseBlock()
{
    if(_condition != NULL)
        delete _condition;
    if(_ifBody != NULL)
        delete _ifBody;
    if(_elseBody != NULL)
        delete _elseBody;
}

QList<Block::ParamType> IfElseBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::BOOLEAN_EXPRESSION);
    return params;
}

void IfElseBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_condition == NULL || _ifBody == NULL || _elseBody == NULL) {
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
        if(value == NULL)
        {
            executionThread.endExecution(NULL);
            return;
        }
        else if (value->toBool())
        {
            //if condition true -> execute if body
            executionThread.setNextBlock(_ifBody);
            m->setValue(2);
        }
        else if (!value->toBool())
        {
            //if condition false -> execute else body
            executionThread.setNextBlock(_elseBody);
            m->setValue(2);
        }

        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool IfElseBlock::addParameter(Block* parameter, int index)
{
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::BOOLEAN_EXPRESSION && parameter->getReturnType() != Block::BOOLEAN_VAR)
        return false;

    _condition = (ExpressionBlock*)parameter;

    return true;
}

bool IfElseBlock::addBody(StatementBlock* body, int index)
{
    if(index < 0 || index > 1 || body == NULL)
        return false;

    if (index == 0)
        _ifBody = body;
    else if (index == 1)
        _elseBody = body;

    return true;
}
