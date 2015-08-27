#include "randomblock.h"

#include "../../executionthread.h"
#include "../../valuemessage.h"
#include "../../numbervalue.h"

#include <QtGlobal>
#include <QTime>

RandomBlock::~RandomBlock()
{
    if (_min != NULL)
        delete _min;

    if (_max != NULL)
        delete _max;
}

QList<Block::ParamType> RandomBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void RandomBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_min == NULL || _max == NULL)
        executionThread.endExecution(NULL);

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
        executionThread.setNextBlock(_min);
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
        executionThread.setNextBlock(_max);
        m->setNumber(2);
        return;
    }

    // Generate random number
    if(m->getNumber() == 2)
    {
        Value* v = executionThread.getReturnValue();
        //check right value
        if(v == NULL || v->getDataType() != Value::NUMBER)
        {
            executionThread.endExecution(NULL);
            return;
        }


        int min = (int) m->getValue()->toDouble();
        int max = (int) v->toDouble();

        QTime time = QTime::currentTime();
        qsrand((uint)time.msec());

        //create return value
        Value* s = new NumberValue(qrand() % ((max + 1) - min) + min);
        executionThread.endExecution(s);
        return;
    }

    executionThread.endExecution(NULL);
}

bool RandomBlock::addParameter(Block* parameter, int index)
{
    if(index < 0 || index > 1 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::NUMBER_EXPRESSION && parameter->getReturnType() != Block::NUMBER_VAR)
        return false;

    if (index == 0)
        _min = (ExpressionBlock*)parameter;
    else if (index == 1)
        _max = (ExpressionBlock*)parameter;

    return true;
}
