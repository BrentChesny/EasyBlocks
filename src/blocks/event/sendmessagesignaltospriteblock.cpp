#include "sendmessagesignaltospriteblock.h"

#include "../../executionthread.h"
#include "../../intmessage.h"
#include "../../signal.h"
#include "../../sprite.h"

SendMessageSignalToSpriteBlock::~SendMessageSignalToSpriteBlock()
{
    if(_message != NULL)
        delete _message;
    if(_spriteTarget != NULL)
        delete _spriteTarget;
}

QList<Block::ParamType> SendMessageSignalToSpriteBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::STRING_EXPRESSION);
    params.append(Block::SPRITE);
    return params;
}

void SendMessageSignalToSpriteBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_message == NULL || _spriteTarget == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //get message
    IntMessage* m = (IntMessage*)executionThread.getMessage();
    if(m == NULL)
    {
        m = new IntMessage(0);
        executionThread.setMessage(m);
    }

    //evaluate message
    if(m->getValue() == 0) {
        executionThread.setNextBlock(_message);
        m->setValue(1);
        return;
    }

    //send message to sprite
    if(m->getValue() == 1) {
        Value* message = executionThread.getReturnValue();
        if(message == NULL || message->getDataType() != Value::STRING) {
            executionThread.endExecution(NULL);
            return;
        }
        Sprite* target = _spriteTarget->getSprite();
        if(target == NULL) {
            executionThread.endExecution(NULL);
            return;
        }
        target->sendSignal(Signal(Signal::MESSAGE, message->toString()));
        executionThread.endExecution(NULL);
    }

    executionThread.endExecution(NULL);
}

bool SendMessageSignalToSpriteBlock::addParameter(Block* parameter, int index)
{
    if(parameter == NULL)
        return false;

    //message
    if(index == 0 && (parameter->getReturnType() == Block::STRING_EXPRESSION || parameter->getReturnType() == Block::STRING_VAR)) {
        _message = (ExpressionBlock*)parameter;
        return true;
    }

    //sprite target
    if(index == 1 && parameter->getReturnType() == Block::SPRITE) {
        _spriteTarget = (SpriteBlock*)parameter;
        return true;
    }

    return false;
}

