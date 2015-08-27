#include "statementsblock.h"
#include "intmessage.h"
#include "executionthread.h"

StatementsBlock::StatementsBlock()
{
}

StatementsBlock::~StatementsBlock()
{
    qDeleteAll(_statements);
}

void StatementsBlock::executeNextStep(ExecutionThread& executionThread) const
{
    IntMessage* message = (IntMessage*)executionThread.getMessage();

    //first step
    if(message == NULL) {
        message = new IntMessage();
        executionThread.setMessage(message);
    }

    //all statements executed
    if(message->getValue() >= _statements.size()) {
        executionThread.endExecution(NULL);
        return;
    }

    //execute next statement
    StatementBlock* nextBlock = _statements.at(message->getValue());
    executionThread.setNextBlock(nextBlock);

    message->setValue(message->getValue()+1);
}

void StatementsBlock::addStatement(StatementBlock* statement)
{
    if(statement != NULL)
        _statements.append(statement);
}
