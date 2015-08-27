#include "lengthblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"
#include "../../numbervalue.h"
#include "../../booleanvalue.h"

LengthBlock::~LengthBlock()
{
    if(_expr != NULL)
        delete _expr;
}

QList<Block::ParamType> LengthBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::STRING_EXPRESSION);
    return params;
}

void LengthBlock::executeNextStep(ExecutionThread& executionThread) const
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

    //Calc length
    if(m->getValue() == 1)
    {
        Value* v = executionThread.getReturnValue();
        if(v == NULL || v->getDataType() != Value::STRING)
        {
            executionThread.endExecution(NULL);
            return;
        }

        //create return value
        Value* s = new NumberValue((double) v->toString().length());
        executionThread.endExecution(s);
        return;
    }

    executionThread.endExecution(NULL);
}

bool LengthBlock::addParameter(Block* parameter, int index)
{
    if(parameter == NULL || (parameter->getReturnType() != Block::STRING_EXPRESSION && parameter->getReturnType() != Block::STRING_VAR))
        return false;

    if(index != 0)
        return false;

    _expr = (ExpressionBlock*)parameter;
    return true;
}

