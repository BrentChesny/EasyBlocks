#include "spriteblockrepr.h"
#include "../project.h"

#include <QDebug>

#include "../spriterepr.h"

SpriteBlockRepr::SpriteBlockRepr(SpriteRepr* sprite, bool locked)
    :BlockRepr(Block::SPRITE, locked), _sprite(sprite)
{
    connect(_sprite, SIGNAL(nameChanged()), this, SLOT(spriteUpdated()));

    spriteUpdated();
}

SpriteBlockRepr::SpriteBlockRepr(const SpriteBlockRepr& spriteBlockRepr)
    : BlockRepr(Block::SPRITE, spriteBlockRepr.isLocked())
{
    _sprite = spriteBlockRepr._sprite;

    connect(_sprite, SIGNAL(nameChanged()), this, SLOT(spriteUpdated()));

    spriteUpdated();
}

BlockRepr* SpriteBlockRepr::copy()
{
    return new SpriteBlockRepr(*this);
}

void SpriteBlockRepr::spriteUpdated()
{
    QStringList paramLabels;
    paramLabels.append(_sprite->getName());
    BlockRepr::setParamLabels(paramLabels);
}

void SpriteBlockRepr::checkExistance(Project* project)
{
    if (project->getIndexOfSprite(_sprite) == -1)
        removeFromParent();
}
