#include "printblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"

PrintBlock::~PrintBlock()
{
    if(_string != NULL)
        delete _string;
}

QList<Block::ParamType> PrintBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::STRING_EXPRESSION);
    return params;
}

void PrintBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_string == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    // get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    // evaluate string
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_string);
        m->setValue(1);
        return;
    }

    //print expression
    if(m->getValue() == 1)
    {
        Value* value = (Value*) executionThread.getReturnValue();
        //if no return value -> end execution
        if(value == NULL || value->getDataType() != Value::STRING)
        {
            executionThread.endExecution(NULL);
            return;
        }

        if(executionThread.getIOHandler() != NULL)
            executionThread.getIOHandler()->writeOutput(value->toString());

        executionThread.endExecution(NULL);
        return;
    }

    //end execution
    executionThread.endExecution(NULL);
}

bool PrintBlock::addParameter(Block* parameter, int index)
{
    //check for correct parameter
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::STRING_EXPRESSION && parameter->getReturnType() != Block::STRING_VAR)
        return false;

    //set the parameter
    _string = (ExpressionBlock*)parameter;

    return true;
}
