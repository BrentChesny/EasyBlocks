#include "spriteblock.h"
#include "executionthread.h"

SpriteBlock::SpriteBlock(Sprite *sprite) : _sprite(sprite)
{
}

void SpriteBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //executing a sprite will not do anything
    executionThread.endExecution(NULL);
}
