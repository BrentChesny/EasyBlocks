#include "spriteresizegraphicsitem.h"

#include <QPainter>

#include "spritegraphicsitem.h"

SpriteResizeGraphicsItem::SpriteResizeGraphicsItem(SpriteGraphicsItem *parent) :
    QObject(NULL), QGraphicsItem(parent), _parent(parent)
{
    _rotate = new RotateGraphicsItem(this);
    _xResize = new XResizeGraphicsItem(this);
    _yResize = new YResizeGraphicsItem(this);
    _xyResize = new XYResizeGraphicsItem(this);

    spriteUpdated();

    connect(parent, SIGNAL(spriteSizeGraphicsUpdated()), this, SLOT(spriteUpdated()));
}

void SpriteResizeGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::DashLine);
    painter->setBrush(Qt::transparent);
    painter->drawRect(boundingRect());
}


void SpriteResizeGraphicsItem::spriteUpdated()
{
    _bounds = _parent->boundingRect().toRect();
    _rotate->setPos(boundingRect().width()/2 + _xResize->boundingRect().width()/2, boundingRect().height()/2 + _yResize->boundingRect().height()/2);
    _xResize->setPos(-boundingRect().width()/2 + _xResize->boundingRect().width()/2, _xResize->boundingRect().height()/2);
    _yResize->setPos(_yResize->boundingRect().width()/2, -boundingRect().height()/2 + _yResize->boundingRect().height()/2);
    _xyResize->setPos(-boundingRect().width()/2 + _xResize->boundingRect().width()/2, -boundingRect().height()/2 + _yResize->boundingRect().height()/2);
}
