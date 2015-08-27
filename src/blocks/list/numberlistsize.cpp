#include "numberlistsize.h"

#include "../../executionthread.h"
#include "../../numbervalue.h"

NumberListSize::~NumberListSize()
{
    if(_list != NULL)
        delete _list;
}

QList<Block::ParamType> NumberListSize::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_LIST);
    return params;
}

void NumberListSize::executeNextStep(ExecutionThread& executionThread) const
{
    if(_list == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    ValueList* list = executionThread.getVarTable()->getList(_list->getListName());

    if(list == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //create return value
    NumberValue* n = new NumberValue(list->getSize());
    executionThread.endExecution(n);
}

bool NumberListSize::addParameter(Block* parameter, int index)
{
    if(parameter == NULL || parameter->getReturnType() != Block::NUMBER_LIST)
        return false;

    if(index != 0)
        return false;

    _list = (ListBlock*)parameter;
    return true;
}
