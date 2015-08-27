#include "spriteheightblock.h"

#include "../../executionthread.h"
#include "../../numbervalue.h"

void SpriteHeightBlock::executeNextStep(ExecutionThread &executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL) {
        executionThread.endExecution(new NumberValue(sprite->getSize().height()));
        return;
    }
    executionThread.endExecution(NULL);
}
