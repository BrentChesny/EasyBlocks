#include "spritewidthblock.h"

#include "../../executionthread.h"
#include "../../numbervalue.h"

void SpriteWidthBlock::executeNextStep(ExecutionThread &executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL) {
        executionThread.endExecution(new NumberValue(sprite->getSize().width()));
        return;
    }
    executionThread.endExecution(NULL);
}
