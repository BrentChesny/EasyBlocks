#include "nextimageblock.h"

#include "../../executionthread.h"

void NextImageBlock::executeNextStep(ExecutionThread& executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL)
        sprite->nextImage();
    executionThread.endExecution(NULL);
}
