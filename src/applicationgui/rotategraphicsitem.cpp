#include "rotategraphicsitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "spriteresizegraphicsitem.h"
#include "spritegraphicsitem.h"

RotateGraphicsItem::RotateGraphicsItem(SpriteResizeGraphicsItem* parent) : QGraphicsItem(parent), _parent(parent)
{

}

void RotateGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::black);
    painter->setBrush(Qt::green);
    painter->drawEllipse(boundingRect());
}

void RotateGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}

void RotateGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //center of sprite
    QPointF center = _parent->getParent()->getSprite()->getPosition();

    //position of mouse
    QPointF mouse = event->scenePos();

    //standard line to define 0 degrees rotation
    QLineF standard  = QLineF(_parent->getParent()->boundingRect().topLeft(), _parent->getParent()->boundingRect().bottomRight());

    //line from center of sprite to mouse
    QLineF rotated = QLineF(center, mouse);

    //set angle
    _parent->getParent()->getSprite()->setRotation(rotated.angleTo(standard));
}

void RotateGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

}
