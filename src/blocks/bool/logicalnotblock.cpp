#include "logicalnotblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"
#include "../../numbervalue.h"
#include "../../booleanvalue.h"

LogicalNotBlock::~LogicalNotBlock()
{
    if(_expr != NULL)
        delete _expr;
}

QList<Block::ParamType> LogicalNotBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::BOOLEAN_EXPRESSION);
    return params;
}

void LogicalNotBlock::executeNextStep(ExecutionThread& executionThread) const
{
    if(_expr == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage();
        executionThread.setMessage(m);
    }

    //evaluate expr
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_expr);
        m->setValue(1);
        return;
    }

    //Check if both _left and _right are evaluated true
    if(m->getValue() == 1)
    {
        Value* v = executionThread.getReturnValue();
        //check right value
        if(v == NULL || v->getDataType() != Value::BOOLEAN)
        {
            executionThread.endExecution(NULL);
            return;
        }

        //create return value
        Value* s = new BooleanValue(!v->toBool());
        executionThread.endExecution(s);
        return;
    }

    executionThread.endExecution(NULL);
}

bool LogicalNotBlock::addParameter(Block* parameter, int index)
{
    if(parameter == NULL || (parameter->getReturnType() != Block::BOOLEAN_EXPRESSION && parameter->getReturnType() != Block::BOOLEAN_VAR))
        return false;

    if(index != 0)
        return false;

    _expr = (ExpressionBlock*)parameter;
    return true;
}

