#include "collidesspriteblock.h"

#include "../../executionthread.h"
#include "../../spriteview.h"
#include "../../booleanvalue.h"

#include <QDebug>
#include <QGraphicsScene>

CollidesSpriteBlock::~CollidesSpriteBlock()
{
    if(_targetSprite != NULL)
        delete _targetSprite;
}

QList<Block::ParamType> CollidesSpriteBlock::getParamTypes() const
{
    QList<Block::ParamType> params;
    params.append(Block::SPRITE);
    return params;
}

void CollidesSpriteBlock::executeNextStep(ExecutionThread& executionThread) const
{
    //check if target sprite is valid
    if(_targetSprite == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    //get the sprites
    Sprite* sprite = executionThread.getSprite();
    Sprite* target = _targetSprite->getSprite();

    if(sprite == NULL || target == NULL) {
        executionThread.endExecution(NULL);
        return;
    }

    SpriteView* s1 = new SpriteView(sprite);
    SpriteView* s2 = new SpriteView(target);
    /*QGraphicsScene* scene = new QGraphicsScene();
    scene->addItem(s1);
    scene->addItem(s2);*/


    /*qDebug() << s1->pos();
    qDebug() << s2->pos();*/

    //test collision
    if(s1->collidesWithItem(s2))
        executionThread.endExecution(new BooleanValue(true));
    else
        executionThread.endExecution(new BooleanValue(false));

    //delete spriteviews
    delete s1;
    delete s2;
}

bool CollidesSpriteBlock::addParameter(Block* parameter, int index)
{
    //check if parameter is correct
    if(index != 0 || parameter == NULL || parameter->getReturnType() != Block::SPRITE)
        return false;

    _targetSprite = (SpriteBlock*) parameter;

    return true;
}
