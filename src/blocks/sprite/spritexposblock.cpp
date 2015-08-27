#include "spritexposblock.h"

#include "../../executionthread.h"
#include "../../numbervalue.h"

void SpriteXPosBlock::executeNextStep(ExecutionThread &executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL) {
        executionThread.endExecution(new NumberValue(sprite->getPosition().x()));
        return;
    }
    executionThread.endExecution(NULL);
}
