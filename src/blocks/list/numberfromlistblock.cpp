#include "numberfromlistblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"
#include "../../numbervalue.h"

NumberFromListBlock::~NumberFromListBlock()
{
    if(_index != NULL)
        delete _index;
    if(_list != NULL)
        delete _list;
}

QList<Block::ParamType> NumberFromListBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_EXPRESSION);
    params.append(Block::NUMBER_LIST);
    return params;
}

void NumberFromListBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if valid
    if(_index == NULL || _list == NULL || _list->getReturnType() != Block::NUMBER_LIST) {
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

    //evaluate index
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_index);
        m->setValue(1);
        return;
    }

    //return value
    if(m->getValue() == 1)
    {
        Value* i = executionThread.getReturnValue();
        if(i == NULL || i->getDataType() != Value::NUMBER) {
            executionThread.endExecution(NULL);
            return;
        }

        //get the value
        Value* v = _list->getValAt((int)i->toDouble(), *executionThread.getVarTable());

        if(v == NULL || v->getDataType() != Value::NUMBER) {
            executionThread.endExecution(NULL);
            return;
        }

        //return a copy
        executionThread.endExecution(v->copy());
        return;
    }

    executionThread.endExecution(NULL);
}

bool NumberFromListBlock::addParameter(Block* parameter, int index)
{
    if(parameter == NULL)
        return false;

    if(index == 0 && (parameter->getReturnType() == Block::NUMBER_EXPRESSION || parameter->getReturnType() == Block::NUMBER_VAR))
    {
        _index = (ExpressionBlock*)parameter;
        return true;
    }

    if(index == 1 && parameter->getReturnType() == Block::NUMBER_LIST)
    {
        _list = (ListBlock*)parameter;
        return true;
    }

    return false;
}
