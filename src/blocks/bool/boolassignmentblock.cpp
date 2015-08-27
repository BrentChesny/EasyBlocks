#include "boolassignmentblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"

BoolAssignmentBlock::~BoolAssignmentBlock()
{
    if(_variable != NULL)
        delete _variable;
    if(_expression != NULL)
        delete _expression;
}

QList<Block::ParamType> BoolAssignmentBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::BOOLEAN_VAR);
    params.append(Block::BOOLEAN_EXPRESSION);
    return params;
}

void BoolAssignmentBlock::executeNextStep(ExecutionThread& executionThread) const
{
    if(_variable == NULL || _expression == NULL)
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

    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_expression);
        m->setValue(1);
        return;
    }

    if(m->getValue() == 1)
    {
        Value* rv = executionThread.getReturnValue();
        if(rv != NULL && executionThread.getVarTable() != NULL)
            _variable->setValue(rv->copy(), *executionThread.getVarTable());

        executionThread.endExecution(NULL);
        return;
    }

    executionThread.endExecution(NULL);
    return;
}

bool BoolAssignmentBlock::addParameter(Block* parameter, int index)
{
    if(parameter == NULL)
        return false;

    if(index == 0 && parameter->getReturnType() == Block::BOOLEAN_VAR) {
        _variable = (VarBlock*)parameter;
        return true;
    }

    if(index == 1 && (parameter->getReturnType() == Block::BOOLEAN_EXPRESSION || parameter->getReturnType() == Block::BOOLEAN_VAR))
    {
        _expression = (ExpressionBlock*)parameter;
        return true;
    }

    return false;
}
