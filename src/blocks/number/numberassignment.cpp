#include "numberassignment.h"

#include "../../executionthread.h"
#include "../../intmessage.h"

NumberAssignment::~NumberAssignment()
{
    if(_variable != NULL)
        delete _variable;
    if(_expression != NULL)
        delete _expression;
}

QList<Block::ParamType> NumberAssignment::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::NUMBER_VAR);
    params.append(Block::NUMBER_EXPRESSION);
    return params;
}

void NumberAssignment::executeNextStep(ExecutionThread& executionThread) const
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

bool NumberAssignment::addParameter(Block* parameter, int index)
{
    if(parameter == NULL)
        return false;

    if(index == 0 && parameter->getReturnType() == Block::NUMBER_VAR) {
        _variable = (VarBlock*)parameter;
        return true;
    }

    if(index == 1 && (parameter->getReturnType() == Block::NUMBER_EXPRESSION || parameter->getReturnType() == Block::NUMBER_VAR))
    {
        _expression = (ExpressionBlock*)parameter;
        return true;
    }

    return false;
}
