#include "addnumbertolistblock.h"

#include "../../executionthread.h"
#include "../../valuemessage.h"

AddNumberToListBlock::~AddNumberToListBlock()
{
    if(_index != NULL)
        delete _index;
    if(_value != NULL)
        delete _value;
    if(_list != NULL)
        delete _list;
}

QList<Block::ParamType> AddNumberToListBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    params.append(Block::NUMBER_LIST);
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void AddNumberToListBlock::executeNextStep(ExecutionThread& executionThread) const
{
    if(_index == NULL || _value == NULL || _list == NULL)
    {
        executionThread.endExecution(NULL);
        return;
    }

    ValueMessage* m = (ValueMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new ValueMessage(0);
        executionThread.setMessage(m);
    }

    //evaluate value
    if(m->getNumber() == 0)
    {
        executionThread.setNextBlock(_value);
        m->setNumber(1);
        return;
    }

    //get value, evaluate index
    if(m->getNumber() == 1)
    {
        Value* returnValue = executionThread.getReturnValue();
        if(returnValue == NULL || returnValue->getDataType() != Value::NUMBER) {
            executionThread.endExecution(NULL);
            return;
        }

        m->setValue(returnValue->copy());
        executionThread.setNextBlock(_index);
        m->setNumber(2);
        return;
    }

    //get index, set value in list
    if(m->getNumber() == 2)
    {
        Value* index = executionThread.getReturnValue();
        if(index == NULL || index->getDataType() != Value::NUMBER) {
            executionThread.endExecution(NULL);
            return;
        }

        _list->setValAt(m->getValue()->copy(), (int)index->toDouble(), *executionThread.getVarTable());
        executionThread.endExecution(NULL);
        return;
    }

    executionThread.endExecution(NULL);
}

bool AddNumberToListBlock::addParameter(Block* parameter, int index)
{
    if(parameter == NULL)
        return false;

    //index
    if(index == 0 && (parameter->getReturnType() == Block::NUMBER_EXPRESSION || parameter->getReturnType() == Block::NUMBER_VAR)) {
        _index = (ExpressionBlock*)parameter;
        return true;
    }

    //list
    if(index == 1 && parameter->getReturnType() == Block::NUMBER_LIST)
    {
        _list = (ListBlock*)parameter;
        return true;
    }

    //value
    if(index == 2 && (parameter->getReturnType() == Block::NUMBER_EXPRESSION || parameter->getReturnType() == Block::NUMBER_VAR)) {
        _value = (ExpressionBlock*)parameter;
        return true;
    }

    return false;
}
