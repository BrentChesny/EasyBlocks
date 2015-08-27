#include "convertnumbertostringblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"
#include "../../stringvalue.h"

ConvertNumberToStringBlock::~ConvertNumberToStringBlock()
{
    if(_number != NULL)
        delete _number;
}

QList<Block::ParamType> ConvertNumberToStringBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void ConvertNumberToStringBlock::executeNextStep(ExecutionThread& executionThread) const
{
    if(_number == NULL) {
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

    //evaluate number
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_number);
        m->setValue(1);
        return;
    }

    //get number, set return value
    if(m->getValue() == 1)
    {
        Value* returnValue = executionThread.getReturnValue();
        if(returnValue == NULL || returnValue->getDataType() != Value::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }

        executionThread.endExecution(new StringValue(returnValue->toString()));
        return;
    }

    executionThread.endExecution(NULL);
}

bool ConvertNumberToStringBlock::addParameter(Block* parameter, int index)
{
    if (parameter == NULL)
        return false;

    if (index == 0 && (parameter->getReturnType() == Block::NUMBER_EXPRESSION || parameter->getReturnType() == Block::NUMBER_VAR)) {
        _number = (ExpressionBlock*) parameter;
        return false;
    }

    return false;
}
