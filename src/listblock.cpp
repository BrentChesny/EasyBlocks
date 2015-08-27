#include "listblock.h"
#include "executionthread.h"

Block::ParamType ListBlock::getReturnType() const
{
    switch(_dataType)
    {
    case Value::BOOLEAN:
        return Block::BOOLEAN_LIST;
    case Value::NUMBER:
        return Block::NUMBER_LIST;
    case Value::STRING:
        return Block::STRING_LIST;
    default:
        return Block::VOID;
    }
}

void ListBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //executing a list will not do anything
    executionThread.endExecution(NULL);
}

Value* ListBlock::getValAt(int position, const VarTable& varTable) const
{
    ValueList* list = varTable.getList(_listName);

    if(list == NULL)
        return NULL;

    Value* value = list->getValueAt(position);

    return value;
}

void ListBlock::setValAt(Value* value, int position, const VarTable& varTable) const
{
    if(value == NULL || value->getDataType() != _dataType)
        return;

    ValueList* list = varTable.getList(_listName);

    if(list == NULL)
        return;

    list->setValueAt(position, value);
}

void ListBlock::addValue(Value *value, const VarTable& varTable) const
{
    if(value == NULL || value->getDataType() != _dataType)
        return;

    ValueList* list = varTable.getList(_listName);

    if(list == NULL)
        return;

    list->addValue(value);
}

int ListBlock::getSize(const VarTable& varTable) const
{
    ValueList* list = varTable.getList(_listName);

    if(list == NULL)
        return 0;

    return list->getSize();
}
