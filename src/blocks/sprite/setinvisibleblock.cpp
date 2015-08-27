#include "setinvisibleblock.h"

#include "../../executionthread.h"
#include "../../spriteview.h"
#include "../../programmodel.h"

void SetInvisibleBlock::executeNextStep(ExecutionThread& executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL)
    {
        sprite->setVisible(false);
    }
    executionThread.endExecution(NULL);
}
