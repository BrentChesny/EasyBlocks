#include "xresizegraphicsitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "spriteresizegraphicsitem.h"
#include "spritegraphicsitem.h"

XResizeGraphicsItem::XResizeGraphicsItem(SpriteResizeGraphicsItem* parent) : QGraphicsItem(parent), _parent(parent)
{

}

void XResizeGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::black);
    painter->drawRect(boundingRect());
}

void XResizeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}

void XResizeGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{

    QSize size = _parent->getParent()->getSprite()->getSize();

    //map event coords to parent
    QPointF position = mapToParent(event->pos());

    //check x value
    int xpos = (int)(-position.x() * 2);
    if(xpos < 0)
        xpos = 0;

    //update size
    size.setWidth(xpos);
    _parent->getParent()->getSprite()->setSize(size);
}

void XResizeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

}
