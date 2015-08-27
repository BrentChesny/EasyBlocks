#include "varblock.h"
#include "executionthread.h"

#include <QDebug>

Block::ParamType VarBlock::getReturnType() const
{
    switch(_dataType)
    {
    case Value::BOOLEAN:
        return Block::BOOLEAN_VAR;
    case Value::NUMBER:
        return Block::NUMBER_VAR;
    case Value::STRING:
        return Block::STRING_VAR;
    default:
        return Block::VOID;
    }
}

void VarBlock::executeNextStep(ExecutionThread& executionThread) const
{
    Value* val = executionThread.getVarTable()->getValue(_varName);

    if(val != NULL && val->getDataType() == _dataType)
        val = val->copy();
    else
        val = NULL;

    executionThread.endExecution(val);
}

void VarBlock::setValue(Value* value, VarTable& varTable) const
{
    if(value == NULL || value->getDataType() != _dataType)
        return;

    varTable.setValue(_varName, value);
}
