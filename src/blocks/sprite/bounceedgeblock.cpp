#include "bounceedgeblock.h"

#include "../../executionthread.h"
#include "../../spriteview.h"
#include "../../programmodel.h"

#include <QDebug>

void BounceEdgeBlock::executeNextStep(ExecutionThread& executionThread) const
{
    Sprite* sprite = executionThread.getSprite();
    if(sprite != NULL)
    {
        SpriteView* s = new SpriteView(sprite);
        QSize screensize = sprite->getProgramModel()->getScreen()->getSize();
        QPainterPath horedges;
        horedges.addRect(-50, 0, screensize.width() + 100, screensize.height());
        QPainterPath veredges;
        veredges.addRect(0, -50, screensize.width(), screensize.height() + 100);
        if (!horedges.contains(s->mapToScene(s->shape())))
            sprite->setRotation(-sprite->getRotation());
        if (!veredges.contains(s->mapToScene(s->shape())))
            sprite->setRotation(-sprite->getRotation() - 180);
    }
    executionThread.endExecution(NULL);
}
