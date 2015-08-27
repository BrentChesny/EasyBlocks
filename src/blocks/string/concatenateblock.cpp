#include "concatenateblock.h"

#include <QDebug>

#include "../../executionthread.h"
#include "../../valuemessage.h"
#include "../../stringvalue.h"


ConcatenateBlock::~ConcatenateBlock()
{
    if(_left != NULL)
        delete _left;
    if(_right != NULL)
        delete _right;
}

QList<Block::ParamType> ConcatenateBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::STRING_EXPRESSION);
    params.append(Block::STRING_EXPRESSION);
    return params;
}

void ConcatenateBlock::executeNextStep(ExecutionThread& executionThread) const
{
    if(_left == NULL || _right == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //get message
    ValueMessage* m = (ValueMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new ValueMessage();
        executionThread.setMessage(m);
    }

    //evaluate left
    if(m->getNumber() == 0)
    {
        executionThread.setNextBlock(_left);
        m->setNumber(1);
        return;
    }

    //evaluate right
    if(m->getNumber() == 1)
    {
        //take copy of returnValue
        m->setValue(executionThread.getReturnValue()->copy());
        //check left value
        if(m->getValue() == NULL || m->getValue()->getDataType() != Value::STRING)
        {
            executionThread.endExecution(NULL);
            return;
        }
        executionThread.setNextBlock(_right);
        m->setNumber(2);
        return;
    }

    //calculate sum
    if(m->getNumber() == 2)
    {
        Value* v = executionThread.getReturnValue();
        //check right value
        if(v == NULL || v->getDataType() != Value::STRING)
        {
            executionThread.endExecution(NULL);
            return;
        }

        //create return value
        Value* s = new StringValue(m->getValue()->toString() + v->toString());
        executionThread.endExecution(s);
        return;
    }

    executionThread.endExecution(NULL);
}

bool ConcatenateBlock::addParameter(Block* parameter, int index)
{
    if(parameter == NULL || (parameter->getReturnType() != Block::STRING_EXPRESSION && parameter->getReturnType() != Block::STRING_VAR))
        return false;

    if(index == 0)
    {
        _left = (ExpressionBlock*)parameter;
        return true;
    }

    if(index == 1)
    {
        _right = (ExpressionBlock*)parameter;
        return true;
    }

    return false;
}
