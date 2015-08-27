#include "spritevisibleblock.h"

#include "../../executionthread.h"
#include "../../booleanvalue.h"

void SpriteVisibleBlock::executeNextStep(ExecutionThread &executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL) {
        executionThread.endExecution(new BooleanValue(sprite->getVisible()));
        return;
    }
    executionThread.endExecution(NULL);
}
