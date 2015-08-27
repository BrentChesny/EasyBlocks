#include "spriterotationblock.h"

#include "../../executionthread.h"
#include "../../numbervalue.h"

void SpriteRotationBlock::executeNextStep(ExecutionThread &executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL) {
        executionThread.endExecution(new NumberValue(sprite->getRotation()));
        return;
    }
    executionThread.endExecution(NULL);
}
