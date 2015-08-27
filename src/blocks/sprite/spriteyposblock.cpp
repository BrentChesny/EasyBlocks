#include "spriteyposblock.h"

#include "../../executionthread.h"
#include "../../numbervalue.h"

void SpriteYPosBlock::executeNextStep(ExecutionThread &executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL) {
        executionThread.endExecution(new NumberValue(sprite->getPosition().y()));
        return;
    }
    executionThread.endExecution(NULL);
}
