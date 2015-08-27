#include "charatblock.h"

#include <QDebug>

#include "../../executionthread.h"
#include "../../valuemessage.h"
#include "../../stringvalue.h"
#include "../../numbervalue.h"


CharAtBlock::~CharAtBlock()
{
    if(_pos != NULL)
        delete _pos;
    if(_string != NULL)
        delete _string;
}

QList<Block::ParamType> CharAtBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    params.append(Block::STRING_EXPRESSION);
    return params;
}

void CharAtBlock::executeNextStep(ExecutionThread& executionThread) const
{
    if(_pos == NULL || _string == NULL) {
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
        executionThread.setNextBlock(_pos);
        m->setNumber(1);
        return;
    }

    //evaluate right
    if(m->getNumber() == 1)
    {
        //take copy of returnValue
        m->setValue(executionThread.getReturnValue()->copy());
        //check left value
        if(m->getValue() == NULL || m->getValue()->getDataType() != Value::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }
        executionThread.setNextBlock(_string);
        m->setNumber(2);
        return;
    }

    // get char at
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
        Value* s = new StringValue(QString(v->toString().at((int) m->getValue()->toDouble())));
        executionThread.endExecution(s);
        return;
    }

    executionThread.endExecution(NULL);
}

bool CharAtBlock::addParameter(Block* parameter, int index)
{
    if (parameter == NULL)
        return false;

    if (index == 0 && (parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR))
        return false;

    if (index == 1 && (parameter->getReturnType() != Block::STRING_EXPRESSION && parameter->getReturnType() != Block::STRING_VAR))
        return false;

    if(index == 0)
    {
        _pos = (ExpressionBlock*)parameter;
        return true;
    }

    if(index == 1)
    {
        _string = (ExpressionBlock*)parameter;
        return true;
    }

    return false;
}

