#include "gotospriteblock.h"

#include "../../executionthread.h"

GoToSpriteBlock::~GoToSpriteBlock()
{
    if(_spriteTarget != NULL)
        delete _spriteTarget;
}

QList<Block::ParamType> GoToSpriteBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::SPRITE);
    return params;
}

void GoToSpriteBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if block is valid for execution
    if(_spriteTarget == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //target sprite to move to
    Sprite* target = _spriteTarget->getSprite();
    if(target == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //Move this sprite to target
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL) {
        sprite->setPosition(target->getPosition());
    }
    executionThread.endExecution(NULL);
}

bool GoToSpriteBlock::addParameter(Block* parameter, int index)
{
    //check for correct parameter
    if(index != 0 || parameter == NULL)
        return false;

    if(parameter->getReturnType() != Block::SPRITE)
        return false;

    //set the parameter
    _spriteTarget = (SpriteBlock*)parameter;

    return true;
}
