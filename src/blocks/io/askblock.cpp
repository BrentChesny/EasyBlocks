#include "askblock.h"

#include "../../executionthread.h"
#include "../../atomicpointermessage.h"
#include "../../stringvalue.h"
#include "../../booleanvalue.h"

AskBlock::~AskBlock()
{
    if(_question != NULL)
        delete _question;
}

QList<Block::ParamType> AskBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::STRING_EXPRESSION);
    return params;
}

void AskBlock::executeNextStep(ExecutionThread& executionThread) const
{
    if(_question == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //get message
    AtomicPointerMessage* m = (AtomicPointerMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new AtomicPointerMessage();
        executionThread.setMessage(m);
    }

    //evaluate question
    if(m->getValue() == 0)
    {
        executionThread.setNextBlock(_question);
        m->setValue(1);
        return;
    }

    //Ask question
    if(m->getValue() == 1)
    {
        Value* v = executionThread.getReturnValue();
        //check return value of question
        if(v == NULL || v->getDataType() != Value::STRING) {
            executionThread.endExecution(NULL);
            return;
        }

        //ask question to the IOHandler
        if(executionThread.getIOHandler() == NULL) {
            executionThread.endExecution(NULL);
            return;
        }
        QAtomicPointer<QString>* atomicPtr = new QAtomicPointer<QString>();
        m->setAtomicPointer(atomicPtr);
        executionThread.getIOHandler()->getInput(v->toString(), atomicPtr);
        m->setValue(2);
        return;
    }

    //Check for answer
    if(m->getValue() == 2)
    {
        if(m->getAtomicPointer() == NULL) {
            executionThread.endExecution(NULL);
            return;
        }

        //if answer received -> return answer
        QString* answer;
        if((answer = m->getAtomicPointer()->load()) != NULL) {
            Value* returnValue = new StringValue(*answer);
            executionThread.endExecution(returnValue);
        }

        //if no answer received -> wait
        return;
    }

    executionThread.endExecution(NULL);
}

bool AskBlock::addParameter(Block* parameter, int index)
{
    if(parameter == NULL || (parameter->getReturnType() != Block::STRING_EXPRESSION && parameter->getReturnType() != Block::STRING_VAR))
        return false;

    if(index != 0)
        return false;

    _question = (ExpressionBlock*)parameter;
    return true;
}
