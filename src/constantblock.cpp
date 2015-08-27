#include "constantblock.h"
#include "executionthread.h"


ConstantBlock::~ConstantBlock()
{
    if(_value != NULL)
        delete _value;
}

Block::ParamType ConstantBlock::getReturnType() const
{
    if(_value == NULL)
        return Block::VOID;

    switch(_value->getDataType())
    {
    case Value::BOOLEAN:
        return Block::BOOLEAN_EXPRESSION;
    case Value::NUMBER:
        return Block::NUMBER_EXPRESSION;
    case Value::STRING:
        return Block::STRING_EXPRESSION;
    default:
        return Block::VOID;
    }
}

void ConstantBlock::executeNextStep(ExecutionThread& executionThread) const
{
    Value *valCopy = NULL;
    if(_value != NULL)
        valCopy = _value->copy();

    executionThread.endExecution(valCopy);
}
