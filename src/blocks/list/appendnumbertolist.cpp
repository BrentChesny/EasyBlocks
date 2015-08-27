#include "appendnumbertolist.h"

#include "../../executionthread.h"
#include "../../intmessage.h"

#include <QDebug>

AppendNumberToList::~AppendNumberToList()
{
    if(_value != NULL)
        delete _value;
    if(_list != NULL)
        delete _list;
}

QList<Block::ParamType> AppendNumberToList::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    params.append(Block::NUMBER_LIST);
    return params;
}

void AppendNumberToList::executeNextStep(ExecutionThread& executionThread) const
{
    if(_value == NULL || _list == NULL)
    {
        executionThread.endExecution(NULL);
        return;
    }

    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    //evaluate value
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_value);
        m->setValue(1);
        return;
    }

    //get value, append to list
    if(m->getValue() == 1)
    {
        Value* returnValue = executionThread.getReturnValue();
        if(returnValue == NULL || returnValue->getDataType() != Value::NUMBER) {
            executionThread.endExecution(NULL);
            return;
        }

        _list->addValue(returnValue->copy(), *executionThread.getVarTable());
        executionThread.endExecution(NULL);
        return;
    }

    executionThread.endExecution(NULL);
}

bool AppendNumberToList::addParameter(Block* parameter, int index)
{
    if(parameter == NULL)
        return false;

    //value
    if(index == 0 && (parameter->getReturnType() == Block::NUMBER_EXPRESSION || parameter->getReturnType() == Block::NUMBER_VAR)) {
        _value = (ExpressionBlock*)parameter;
        return true;
    }

    //list
    if(index == 1 && parameter->getReturnType() == Block::NUMBER_LIST)
    {
        _list = (ListBlock*)parameter;
        return true;
    }

    return false;
}
