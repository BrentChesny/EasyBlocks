#include "setvisibleblock.h"

#include "../../executionthread.h"
#include "../../spriteview.h"
#include "../../programmodel.h"

void SetVisibleBlock::executeNextStep(ExecutionThread& executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL)
    {
        sprite->setVisible(true);
    }
    executionThread.endExecution(NULL);
}
