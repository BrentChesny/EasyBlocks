#include "xyresizegraphicsitem.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

#include "spriteresizegraphicsitem.h"
#include "spritegraphicsitem.h"

XYResizeGraphicsItem::XYResizeGraphicsItem(SpriteResizeGraphicsItem* parent) : QGraphicsItem(parent), _parent(parent)
{

}

void XYResizeGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    painter->setPen(Qt::white);
    painter->setBrush(Qt::black);
    painter->drawRect(boundingRect());
}

void XYResizeGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{

}

void XYResizeGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    //map event coords to parent
    QPointF position = mapToParent(event->pos());

    //check x value
    int width = (int)(-position.x() * 2);
    if(width < 0)
        width = 0;

    //check y value
    int height = (int)(-position.y() * 2);
    if(height < 0)
        height = 0;

    //update size
    _parent->getParent()->getSprite()->setSize(QSize(width, height));
}

void XYResizeGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

}
